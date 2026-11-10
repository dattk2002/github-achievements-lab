#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace lab {
namespace {
void check(std::vector<int> costs, int expected) {
    const auto before = costs;
    const int actual = Solution{}.climbStairs(static_cast<int>(costs.size()), costs);
    if (actual != expected || costs != before) {
        std::cerr << "n=" << costs.size() << ": expected " << expected
                  << ", got " << actual << "; input must remain unchanged\n";
        std::exit(EXIT_FAILURE);
    }
}

// Enumerate complete paths forwards, with no DP or memoization.
void enumerate(const std::vector<int>& costs, int position, int total, int& best) {
    const int n = static_cast<int>(costs.size());
    if (position == n) {
        best = std::min(best, total);
        return;
    }
    for (int jump = 1; jump <= 3 && position + jump <= n; ++jump) {
        enumerate(costs, position + jump,
                  total + costs[position + jump - 1] + jump * jump, best);
    }
}
}  // namespace

void run_tests() {
    check({1}, 2);
    check({10000}, 10001);
    check({1, 1}, 4);             // Two unit jumps beat one double jump.
    check({10000, 1}, 5);         // Skip the expensive first landing.
    check({10000, 10000, 1}, 10); // A triple jump is necessary for the optimum.
    check({1, 10000, 1}, 7);      // Both 1+2 and 2+1 jump orders are considered.
    check({2, 2}, 6);             // Equal-cost alternatives.
    check({1, 100, 100, 1}, 12);  // Must pay for the final landing.
    check({2, 2, 2, 2, 2}, 15);
    check(std::vector<int>(100000, 1), 200000);
    // 33332 jumps of length 3 and two of length 2 minimize squared lengths.
    check(std::vector<int>(100000, 10000), 333639996);

    int cases = 0;
    const int values[] = {1, 4, 10000};
    for (int n = 1; n <= 7; ++n) {
        int count = 1;
        for (int i = 0; i < n; ++i) count *= 3;
        for (int code = 0; code < count; ++code) {
            int digits = code;
            std::vector<int> costs(n);
            for (int& cost : costs) {
                cost = values[digits % 3];
                digits /= 3;
            }
            int expected = std::numeric_limits<int>::max();
            enumerate(costs, 0, 0, expected);
            check(costs, expected);
            ++cases;
        }
    }
    std::cout << "climbing stairs II: boundary cases and " << cases
              << " exhaustive inputs passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
