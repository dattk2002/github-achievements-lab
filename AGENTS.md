# C++ learning lab

- Keep each PR focused on one complete educational task.
- New lessons live in `lessons/NN-topic/` with `lesson.hpp`, `test.cpp`, and
  a Vietnamese `README.md` covering the contract, algorithm, complexity,
  runnable examples, edge cases, and exercises.
- Use C++17, namespace `lab`, and standard libraries. No new dependencies.
- Write meaningful tests before implementation. Tests must fail with a
  nonzero exit code even when `NDEBUG` is defined; do not rely on `assert`.
- Run `make test` and `git diff --check` before committing.
- Credit Codex-assisted work accurately with the trailer
  `Co-authored-by: OpenAI Codex <codex@openai.com>`; preserve it on squash.
- A scheduled task prioritizes the public LeetCode Daily, using the first
  unfinished curriculum entry as fallback. No Premium or duplicate tasks.
  Link the original problem; write original examples, solution and prose.
  Do not copy the full statement, editorial or others' solutions.
  Do not create filler, split a cohesive lesson into artificial PRs,
  modify automation to bypass checks, or invent fallback tasks.
- Scheduled worker/reviewer agents must not perform Git/GitHub writes:
  the reviewed outer controller owns commit, push, PR creation and merge.
- If a write has an uncertain result, inspect its state before taking
  another action. Preserve failed work for inspection; never reset or
  discard it automatically.
