# Daily C++ Learning Implementation Plan

> **For agentic workers:** Use superpowers:executing-plans to implement this plan inline; use an independent code reviewer before merge.

**Goal:** Deliver useful C++ lessons through tested, Codex-coauthored PRs and an authorized daily schedule.

**Architecture:** A C++17 lesson consists of an implementation, executable tests and Vietnamese explanation. A local Python controller prioritizes the public LeetCode Daily with a finite curriculum fallback, invokes sandboxed Codex for implementation and independent review, verifies CI, and squash-merges an exact reviewed head.

**Tech Stack:** C++17, Python standard library, Make, Git, gh CLI, Codex CLI, user crontab.

**Spec:** User-approved scope: one complete task per scheduled run, actual tested changes only, 09:00 Asia/Ho_Chi_Minh, progress toward both achievements without guarantees about GitHub award timing. Subsequent steering: prioritize LeetCode Daily; language flexible (C++ chosen initially for the existing tested pipeline), no submissions to the source site.

## Global Constraints

- Only `dattk2002/github-achievements-lab`; no external messages or other-service submissions.
- Maximum one scheduled lesson per day; no minimum quota or fabricated tasks beyond public Daily/curated fallback.
- Preserve existing README and all failed work; never reset or retry uncertain writes.
- Use `Co-authored-by: OpenAI Codex <codex@openai.com>` on real Codex-assisted work.
- Codex workers cannot publish; the controller checks scope, tests and review first.

## Review Focus

- Duplicate runs: a file lock and persisted state prevent concurrent or repeated merges.
- Dirty checkout or incomplete lesson: stop without overwriting work.
- Empty, symlink or out-of-scope changes: reject before staging.
- Test failure, declined review or missing CI: preserve work and stop before merge.
- Uncertain GitHub write: persist phase before the write; no automatic replay.

## Tasks

- [x] Inspect remote, authenticated identity, empty initial repository and available local tools.
- [x] Write lesson boundary/oracle tests and controller guard tests; observe missing implementation failures.
- [x] Implement binary search, curriculum, controller, documentation and CI; run `make test`.
- [x] Add a public Daily source reader, duplicate/premium/staleness guards and finite fallback; verify live API and offline tests.
- [x] Independently review and fix objective findings; verify again (26 Python tests and C++ oracle tests pass, including the full bubblewrap run).
- [ ] Inspect exact diff, commit with Codex attribution, push one feature branch and create PR.
- [ ] Verify CI, squash merge and verify commit author/coauthor linkage through GitHub API.
- [ ] Install reviewed controller and run one real next-lesson cycle as end-to-end verification.
- [ ] Install 09:00 user cron without replacing unrelated entries; verify schedule and safe duplicate skip.
- [ ] Record actual PR URLs, test results, schedule and award state in delivery.
