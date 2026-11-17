#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Enumerate multiplicities of each denomination; order never creates a new way.
int oracle(const std::vector<int>& coins, std::size_t index, int remaining) {
    if (index == coins.size()) return remaining == 0 ? 1 : 0;
    int ways = 0;
    for (int used = 0; used <= remaining; used += coins[index])
        ways += oracle(coins, index + 1, remaining - used);
    return ways;
}

void check(std::vector<int> coins, int amount, int expected) {
    const auto original = coins;
    require(lab::Solution{}.change(amount, coins) == expected, "LC518: combination count differs");
    require(coins == original, "LC518: coins changed");
}

void invalid(std::vector<int> coins, int amount) {
    const auto original = coins;
    bool threw = false;
    try { (void)lab::Solution{}.change(amount, coins); }
    catch (const std::invalid_argument&) { threw = true; }
    require(threw && coins == original, "LC518: invalid arguments must throw without mutation");
}

int main() {
    check({2, 3, 7}, 12, 4);
    check({3, 2}, 7, 1);
    check({4, 6}, 7, 0);
    check({4}, 12, 1);
    check({5}, 0, 1);
    check({}, 0, 1);
    check({}, 8, 0);
    std::size_t cases = 0;
    for (unsigned mask = 0; mask < (1U << 7); ++mask) {
        std::vector<int> coins;
        for (int value = 1; value <= 7; ++value)
            if ((mask & (1U << (value - 1))) != 0) coins.push_back(value);
        for (int amount = 0; amount <= 24; ++amount) {
            const int expected = oracle(coins, 0, amount);
            check(coins, amount, expected);
            std::reverse(coins.begin(), coins.end());
            check(coins, amount, expected);
            ++cases;
        }
    }
    check({1, 2}, 5000, 2501);
    check({5000}, 5000, 1);
    std::vector<int> even;
    for (int coin = 2; coin <= 600; coin += 2) even.push_back(coin);
    // Huge counts for even subtotals must not overflow when the final answer is zero.
    check(even, 4999, 0);
    bool overflow = false;
    const auto original = even;
    try { (void)lab::Solution{}.change(5000, even); }
    catch (const std::overflow_error&) { overflow = true; }
    require(overflow && even == original, "LC518: unrepresentable final count must throw");
    invalid({1}, -1);
    invalid({0, 2}, 4);
    invalid({-2, 3}, 0);
    invalid({2, 2}, 4);
    std::cout << "LC518: fixed, " << cases << " multiplicity-oracle cases in both orders, invalid and overflow cases passed\n";
}
