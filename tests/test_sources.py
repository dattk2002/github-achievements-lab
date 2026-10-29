from datetime import date
import unittest

from automation.sources import daily_from_payload


def payload():
    return {"data": {"activeDailyCodingChallengeQuestion": {
        "date": "2026-10-29", "link": "/problems/example-task/",
        "question": {"questionFrontendId": "1234", "title": "Example Task",
                     "titleSlug": "example-task", "difficulty": "Easy",
                     "isPaidOnly": False,
                     "content": "<p>Compute a result.</p><p>Bound: n &lt; 100.</p>",
                     "codeSnippets": [{"langSlug": "cpp", "code": "class Solution {};"}]}
    }}}


class DailySourceTests(unittest.TestCase):
    def test_maps_public_daily_to_a_unique_source_linked_lesson(self):
        result = daily_from_payload(payload(), date(2026, 10, 29))
        self.assertEqual(result["id"], "leetcode-1234-example-task")
        self.assertEqual(result["source_url"], "https://leetcode.com/problems/example-task/")
        self.assertEqual(result["source_date"], "2026-10-29")
        self.assertIn("Bound: n < 100.", result["problem_data"])
        self.assertNotIn("<p>", result["problem_data"])

    def test_skips_premium_content(self):
        data = payload()
        data["data"]["activeDailyCodingChallengeQuestion"]["question"]["isPaidOnly"] = True
        self.assertIsNone(daily_from_payload(data, date(2026, 10, 29)))

    def test_rejects_a_stale_daily_instead_of_labeling_it_today(self):
        self.assertIsNone(daily_from_payload(payload(), date(2026, 10, 30)))

    def test_rejects_api_errors_and_unavailable_statements(self):
        self.assertIsNone(daily_from_payload({"errors": [{"message": "Unavailable"}]},
                                            date(2026, 10, 29)))
        data = payload()
        data["data"]["activeDailyCodingChallengeQuestion"]["question"]["content"] = None
        self.assertIsNone(daily_from_payload(data, date(2026, 10, 29)))

    def test_rejects_path_escape_or_mismatched_source_link(self):
        for field, value in (("titleSlug", "../../outside"),
                             ("questionFrontendId", "../1234")):
            data = payload()
            data["data"]["activeDailyCodingChallengeQuestion"]["question"][field] = value
            with self.subTest(field=field), self.assertRaises(ValueError):
                daily_from_payload(data, date(2026, 10, 29))
        data = payload()
        data["data"]["activeDailyCodingChallengeQuestion"]["link"] = "https://other.invalid/"
        with self.assertRaises(ValueError):
            daily_from_payload(data, date(2026, 10, 29))

    def test_changed_api_shapes_are_treated_as_unavailable(self):
        for data in ([], None, {"data": []},
                     {"data": {"activeDailyCodingChallengeQuestion": []}},
                     {"data": {"activeDailyCodingChallengeQuestion": {
                         "date": "2026-10-29", "question": []}}}):
            with self.subTest(payload=data):
                self.assertIsNone(daily_from_payload(data, date(2026, 10, 29)))


if __name__ == "__main__":
    unittest.main()
