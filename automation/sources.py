"""Read public LeetCode Daily data; never log in or submit solutions."""

from html.parser import HTMLParser
from http.client import HTTPException
import json
import re
import urllib.error
import urllib.request


class PlainText(HTMLParser):
    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.parts = []

    def handle_data(self, data):
        self.parts.append(data)


def daily_from_payload(payload, today):
    if not isinstance(payload, dict) or not isinstance(payload.get("data"), dict):
        return None
    daily = payload["data"].get("activeDailyCodingChallengeQuestion")
    if (payload.get("errors") or not isinstance(daily, dict)
            or daily.get("date") != today.isoformat()):
        return None
    question = daily.get("question")
    if not isinstance(question, dict):
        return None
    content = question.get("content")
    if question.get("isPaidOnly") is not False or not content:
        return None
    slug = question.get("titleSlug", "")
    number = question.get("questionFrontendId", "")
    if not re.fullmatch(r"[a-z0-9]+(?:-[a-z0-9]+)*", slug) or len(slug) > 150:
        raise ValueError("Invalid LeetCode problem slug")
    if not re.fullmatch(r"[0-9]{1,6}", number):
        raise ValueError("Invalid LeetCode problem number")
    if daily.get("link") != f"/problems/{slug}/":
        raise ValueError("Unexpected LeetCode problem link")
    if not isinstance(content, str) or len(content) > 80_000:
        raise ValueError("Unexpected LeetCode statement size")
    parser = PlainText()
    parser.feed(content)
    snippets = question.get("codeSnippets") or []
    if not isinstance(snippets, list):
        return None
    interface = next((item.get("code", "") for item in snippets
                      if isinstance(item, dict) and item.get("langSlug") == "cpp"), "")
    return {
        "id": f"leetcode-{number}-{slug}",
        "title": f"LeetCode {number}: {question['title']}",
        "source_url": f"https://leetcode.com/problems/{slug}/",
        "source_date": daily["date"],
        "difficulty": question.get("difficulty", "Unknown"),
        "requirements": "Solve this public Daily in C++17 with a standalone test suite. "
                        "Keep the problem's semantics and constraints; adapt the C++ "
                        "interface to namespace lab. Explain your own algorithm and tests.",
        # This data is provided to the worker, not copied into the repository.
        "problem_data": "\n".join(parser.parts).strip(),
        "cpp_interface": interface,
    }


def fetch_leetcode_daily(today):
    query = """query { activeDailyCodingChallengeQuestion { date link question {
      questionFrontendId title titleSlug difficulty isPaidOnly content
      codeSnippets { langSlug code }
    } } }"""
    request = urllib.request.Request(
        "https://leetcode.com/graphql/",
        data=json.dumps({"query": query}).encode(),
        headers={"Content-Type": "application/json",
                 "User-Agent": "github-achievements-lab/1.0",
                 "Referer": "https://leetcode.com/"},
    )
    try:
        with urllib.request.urlopen(request, timeout=20) as response:
            data = response.read(1_000_001)
        if len(data) > 1_000_000:
            raise ValueError("LeetCode response is too large")
        return daily_from_payload(json.loads(data), today)
    except (urllib.error.URLError, HTTPException, TimeoutError,
            ValueError, KeyError, TypeError) as error:
        print(f"LeetCode Daily unavailable ({type(error).__name__}); using curriculum fallback.")
        return None
