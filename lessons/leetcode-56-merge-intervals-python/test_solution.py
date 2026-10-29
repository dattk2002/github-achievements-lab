import itertools
import random
import unittest

from solution import merge_intervals


class MergeIntervalsTests(unittest.TestCase):
    def test_overlap_touching_nested_and_unsorted(self):
        self.assertEqual(merge_intervals([[9, 12], [2, 5], [4, 8], [8, 9], [3, 3]]),
                         [[2, 12]])

    def test_empty_singleton_and_separate_points(self):
        for source, expected in [([], []), ([[4, 4]], [[4, 4]]),
                                 ([[7, 7], [-2, -2]], [[-2, -2], [7, 7]])]:
            with self.subTest(source=source):
                self.assertEqual(merge_intervals(source), expected)

    def test_no_input_mutation_or_output_aliasing(self):
        source = [[6, 10], [1, 3], [2, 4]]
        original = [row[:] for row in source]
        result = merge_intervals(source)
        self.assertEqual(source, original)
        result[0][0] = -100
        self.assertEqual(source, original)

    def test_small_random_cases_against_half_step_coverage(self):
        # Half-integer points distinguish [1, 1] + [2, 2] from [1, 2].
        rng = random.Random(56)
        for _ in range(500):
            source = [sorted(rng.choices(range(-4, 5), k=2))
                      for _ in range(rng.randrange(12))]
            covered = {p for left, right in source for p in range(2 * left, 2 * right + 1)}
            expected = []
            for _, group in itertools.groupby(enumerate(sorted(covered)),
                                               key=lambda pair: pair[1] - pair[0]):
                points = [point for _, point in group]
                expected.append([points[0] // 2, points[-1] // 2])
            self.assertEqual(merge_intervals(source), expected, source)

    def test_ten_thousand_disjoint_intervals(self):
        source = [[3 * i, 3 * i + 1] for i in reversed(range(10_000))]
        self.assertEqual(merge_intervals(source), list(reversed(source)))


if __name__ == '__main__':
    unittest.main()
