from collections import deque
import random
import unittest

from solution import coin_change


def oracle(coins, amount):
    queue = deque([(0, 0)])
    seen = {0}
    while queue:
        value, depth = queue.popleft()
        if value == amount:
            return depth
        for coin in coins:
            candidate = value + coin
            if candidate <= amount and candidate not in seen:
                seen.add(candidate)
                queue.append((candidate, depth + 1))
    return -1


class CoinChangeTests(unittest.TestCase):
    def test_greedy_is_not_always_optimal_and_coins_are_reusable(self):
        self.assertEqual(coin_change([1, 3, 4], 6), 2)
        self.assertEqual(coin_change([3], 9), 3)

    def test_zero_impossible_large_coins_and_empty_denominations(self):
        for coins, amount, expected in [([2, 6], 7, -1), ([3], 0, 0),
                                        ([2**31 - 1, 2], 4, 2),
                                        ([], 0, 0), ([], 5, -1)]:
            with self.subTest(coins=coins, amount=amount):
                self.assertEqual(coin_change(coins, amount), expected)

    def test_duplicates_order_and_input_preservation(self):
        coins = [7, 2, 7, 3]
        self.assertEqual(coin_change(coins, 13), 3)
        self.assertEqual(coins, [7, 2, 7, 3])

    def test_five_hundred_small_cases_against_breadth_first_search(self):
        rng = random.Random(322)
        for _ in range(500):
            coins = [rng.randrange(1, 15) for _ in range(rng.randrange(7))]
            amount = rng.randrange(61)
            self.assertEqual(coin_change(coins, amount), oracle(coins, amount),
                             (coins, amount))

    def test_maximum_amount(self):
        self.assertEqual(coin_change([1], 10_000), 10_000)
        self.assertEqual(coin_change([25, 100, 200], 10_000), 50)
        self.assertEqual(coin_change([6, 10], 9_999), -1)


if __name__ == '__main__':
    unittest.main()
