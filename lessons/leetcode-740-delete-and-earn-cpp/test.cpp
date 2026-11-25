#include "lesson.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
// Enumerate subsets of distinct values; adjacent values cannot both be earned.
int oracle(const std::vector<int>& values) {
    std::array<int, 9> points{};
    for (int value : values) points[value] += value;
    int best = 0;
    for (unsigned mask = 0; mask < (1U << 8); ++mask) {
        if ((mask & (mask << 1)) != 0) continue;
        int sum = 0;
        for (int value = 1; value <= 8; ++value)
            if ((mask & (1U << (value - 1))) != 0) sum += points[value];
        best = std::max(best, sum);
    }
    return best;
}
void check(std::vector<int> values, int expected) {
    const auto original = values;
    require(lab::Solution{}.deleteAndEarn(values) == expected, "earnings mismatch");
    require(values == original, "input changed");
}
int main() {
    check({1, 1, 4, 4, 5}, 10);
    check({7}, 7);
    check({}, 0);
    check({2, 3}, 3);
    check({1, 3, 5, 7}, 16);
    check({3, 3, 3, 4, 4, 5, 5}, 19);
    std::mt19937 random(740);
    for (int trial = 0; trial < 2000; ++trial) {
        std::vector<int> values(random() % 21);
        for (int& value : values) value = 1 + static_cast<int>(random() % 8);
        check(values, oracle(values));
    }
    check(std::vector<int>(20000, 10000), 200000000);
    check({1, 10000}, 10001);
    std::cout << "LC740: fixed, 2000 subset-oracle and boundary cases passed\n";
}
