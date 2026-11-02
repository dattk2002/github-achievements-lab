#include "lesson.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace lab {
namespace {
void check(std::vector<int> nums, int expected) {
    const auto before = nums;
    Solution solution;
    const int actual = solution.minMoves2(nums);
    if (actual != expected || nums != before) {
        std::cerr << "n=" << nums.size() << ": expected " << expected
                  << ", got " << actual << " (input must be preserved)\n";
        std::exit(EXIT_FAILURE);
    }
}

// Independent oracle: try every integer destination in the small input range.
int exhaustive_target(const std::vector<int>& nums) {
    const auto bounds = std::minmax_element(nums.begin(), nums.end());
    int best = std::numeric_limits<int>::max();
    for (int target = *bounds.first; target <= *bounds.second; ++target) {
        int cost = 0;
        for (int value : nums) cost += std::abs(value - target);
        best = std::min(best, cost);
    }
    return best;
}
}  // namespace

void run_tests() {
    // Distinguishes median from minimum, mean, and a constant-zero answer.
    check({0, 0, 12}, 12);
    check({8, 2, 5}, 6);
    check({-8, -3, -1}, 7);
    check({-4, 0, 7}, 11);
    check({9, -3, 6, 0}, 18);
    check({6, 6, 6, 6}, 0);
    check({-1000000000}, 0);
    check({1000000000}, 0);
    check({-1000000000, 1000000000}, 2000000000);
    check({-1000000000, 0, 1000000000, 147483647}, 2147483647);
    check({10, 10, 10, -5, 10}, 15);
    check({5, 4, 3, 2, 1}, 6);
    check(std::vector<int>(100000, 1000000000), 0);
    check(std::vector<int>(100000, -1000000000), 0);
    std::vector<int> large(100000, -1000000000);
    large.back() = 1000000000;
    check(large, 2000000000);
    large.assign(100000, 1000000000);
    large.front() = -1000000000;
    check(large, 2000000000);
    for (std::size_t i = 0; i < large.size(); ++i) large[i] = i % 2 == 0 ? -7 : 11;
    check(large, 900000);

    int cases = 0;
    for (int n = 1; n <= 6; ++n) {
        int combinations = 1;
        for (int i = 0; i < n; ++i) combinations *= 5;
        for (int code = 0; code < combinations; ++code) {
            std::vector<int> nums(n);
            int digits = code;
            for (int& value : nums) {
                value = digits % 5 - 2;
                digits /= 5;
            }
            check(nums, exhaustive_target(nums));
            ++cases;
        }
    }
    std::cout << "minMoves2: boundary cases and " << cases
              << " exhaustive-target cases passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
