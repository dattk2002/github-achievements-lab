import json
from pathlib import Path
import subprocess
import shutil
import sys
import tempfile
import time
import unittest
from datetime import datetime
from unittest.mock import patch
from zoneinfo import ZoneInfo

import automation.daily as daily
from automation.daily import next_lesson, changed_paths, validate_lesson_changes


class DailyLessonTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.lesson = {"id": "02-linear-search", "title": "Linear search"}
        (self.root / "curriculum.json").write_text(json.dumps([self.lesson]))

    def complete_lesson(self):
        directory = self.root / "lessons" / self.lesson["id"]
        directory.mkdir(parents=True)
        for name in ("README.md", "lesson.hpp", "test.cpp"):
            (directory / name).write_text("example content\n")
        return directory

    def test_selects_an_unfinished_lesson(self):
        self.assertEqual(next_lesson(self.root), self.lesson)

    def test_stops_when_the_curriculum_is_complete(self):
        self.complete_lesson()
        self.assertIsNone(next_lesson(self.root))

    def test_refuses_a_partial_lesson_instead_of_overwriting_it(self):
        directory = self.root / "lessons" / self.lesson["id"]
        directory.mkdir(parents=True)
        (directory / "README.md").write_text("user work\n")
        with self.assertRaisesRegex(ValueError, "partial"):
            next_lesson(self.root)

    def test_rejects_a_curriculum_path_escape(self):
        self.lesson["id"] = "../../outside"
        (self.root / "curriculum.json").write_text(json.dumps([self.lesson]))
        with self.assertRaises(ValueError):
            next_lesson(self.root)

    def test_accepts_a_complete_lesson_only_change(self):
        directory = self.complete_lesson()
        paths = [str(path.relative_to(self.root)) for path in directory.iterdir()]
        validate_lesson_changes(self.root, self.lesson["id"], paths)

    def test_rejects_changes_to_workflows_or_other_lessons(self):
        self.complete_lesson()
        for path in (".github/workflows/test.yml", "lessons/01-other/test.cpp",
                     "automation/daily.py", "lessons/02-linear-search/extra.sh"):
            with self.subTest(path=path), self.assertRaises(ValueError):
                validate_lesson_changes(self.root, self.lesson["id"], [path])

    def test_rejects_missing_or_empty_deliverables(self):
        directory = self.complete_lesson()
        (directory / "test.cpp").write_text("")
        with self.assertRaises(ValueError):
            validate_lesson_changes(self.root, self.lesson["id"],
                                    ["lessons/02-linear-search/lesson.hpp"])

    def test_rejects_a_symlink_deliverable(self):
        directory = self.complete_lesson()
        (directory / "lesson.hpp").unlink()
        (directory / "lesson.hpp").symlink_to(directory / "README.md")
        with self.assertRaises(ValueError):
            validate_lesson_changes(self.root, self.lesson["id"],
                                    ["lessons/02-linear-search/lesson.hpp"])

    def test_changed_paths_include_untracked_files_and_tracked_edits(self):
        def git(*args):
            return subprocess.run(["git", *args], cwd=self.root, check=True,
                                  capture_output=True, text=True)
        git("init", "-q")
        (self.root / "tracked.txt").write_text("before\n")
        git("add", ".")
        git("-c", "user.name=Test", "-c", "user.email=test@example.invalid",
            "commit", "-qm", "Initial fixture")
        (self.root / "tracked.txt").write_text("after\n")
        (self.root / "new.txt").write_text("new\n")
        self.assertEqual(set(changed_paths(self.root)), {"tracked.txt", "new.txt"})

    def test_child_commands_do_not_inherit_stdin(self):
        source = (
            "from automation.daily import command; import sys; "
            "print(command([sys.executable, '-c', "
            "'import sys; print(repr(sys.stdin.read()))']))"
        )
        result = subprocess.run([sys.executable, "-c", source],
                                cwd=Path(__file__).resolve().parents[1],
                                input="unexpected inherited input", text=True,
                                capture_output=True, check=True, timeout=5)
        self.assertEqual(result.stdout.strip(), "''")

    def test_stops_before_auth_or_writes_after_an_uncertain_run(self):
        (self.root / "state.json").write_text(json.dumps({"phase": "publishing"}))
        with patch.object(daily, "command", side_effect=AssertionError("must not run")):
            daily.run_daily(self.root)

    def test_stops_before_auth_or_writes_after_same_day_success(self):
        today = datetime.now(ZoneInfo("Asia/Ho_Chi_Minh")).date().isoformat()
        (self.root / "state.json").write_text(json.dumps({"phase": "merged", "date": today}))
        with patch.object(daily, "command", side_effect=AssertionError("must not run")):
            daily.run_daily(self.root)

    def init_git(self):
        def git(*args):
            return subprocess.run(["git", *args], cwd=self.root, check=True,
                                  capture_output=True, text=True).stdout.strip()
        git("init", "-q")
        git("config", "user.name", "Test")
        git("config", "user.email", "test@example.invalid")
        git("add", ".")
        git("commit", "-qm", "Base fixture")
        return git

    def test_rejects_a_clean_checkout_ahead_of_the_pinned_base(self):
        git = self.init_git()
        base = git("rev-parse", "HEAD")
        (self.root / "unreviewed.txt").write_text("unreviewed work\n")
        git("add", ".")
        git("commit", "-qm", "Local-only commit")
        with self.assertRaisesRegex(ValueError, "base"):
            daily.validate_base(self.root, base)

    def test_rejects_a_different_effective_push_url(self):
        git = self.init_git()
        git("remote", "add", "origin", daily.REMOTE)
        git("config", "remote.origin.pushurl", str(self.root / "other-repo"))
        with self.assertRaisesRegex(ValueError, "origin"):
            daily.validate_remote(self.root)

    def test_completed_commands_cannot_leave_background_writers(self):
        marker = self.root / "late-write.txt"
        child = f"import time; from pathlib import Path; time.sleep(0.3); Path({str(marker)!r}).write_text('late')"
        parent = ("import subprocess,sys; subprocess.Popen([sys.executable,'-c',"
                  f"{child!r}],stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)")
        daily.command([sys.executable, "-c", parent], timeout=2)
        time.sleep(0.5)
        self.assertFalse(marker.exists(), "A child survived its completed command")

    def test_prefers_a_new_daily_over_the_curriculum(self):
        lesson = {"id": "leetcode-1234-example", "title": "Public Daily"}
        with patch.object(daily, "fetch_leetcode_daily", return_value=lesson):
            self.assertEqual(daily.select_lesson(self.root, "2026-10-29"), lesson)

    def test_falls_back_when_daily_source_is_unavailable(self):
        with patch.object(daily, "fetch_leetcode_daily", return_value=None):
            self.assertEqual(daily.select_lesson(self.root, "2026-10-29"), self.lesson)

    def test_does_not_republish_an_already_completed_daily(self):
        lesson = {"id": "leetcode-1234-example", "title": "Public Daily"}
        directory = self.root / "lessons" / lesson["id"]
        directory.mkdir(parents=True)
        for name in daily.DELIVERABLES:
            (directory / name).write_text("completed\n")
        with patch.object(daily, "fetch_leetcode_daily", return_value=lesson):
            self.assertEqual(daily.select_lesson(self.root, "2026-10-29"), self.lesson)

    def test_validates_real_nul_terminated_committed_diff(self):
        git = self.init_git()
        base = git("rev-parse", "HEAD")
        self.complete_lesson()
        git("add", ".")
        git("commit", "-qm", "Complete lesson")
        paths = daily.committed_paths(self.root, base, "HEAD")
        self.assertEqual(len(paths), 3)
        validate_lesson_changes(self.root, self.lesson["id"], paths)

    @unittest.skipUnless(shutil.which("bwrap"), "Linux bubblewrap integration")
    def test_worker_namespace_removes_even_detached_children(self):
        marker = self.root / "detached-write.txt"
        child = f"import time; from pathlib import Path; time.sleep(0.3); Path({str(marker)!r}).write_text('late')"
        parent = ("import subprocess,sys; subprocess.Popen([sys.executable,'-c',"
                  f"{child!r}],start_new_session=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)")
        daily.command(daily.pid_namespace_args([sys.executable, "-c", parent]), timeout=5)
        time.sleep(0.5)
        self.assertFalse(marker.exists(), "Detached child escaped worker lifetime")


if __name__ == "__main__":
    unittest.main()
