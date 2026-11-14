#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

namespace lab {
namespace {
void check(std::vector<int> nums, int l, int r, int expected) {
    const auto before = nums;
    const int actual = Solution{}.minimumSumSubarray(nums, l, r);
    if (actual != expected || nums != before) {
        std::cerr << "n=" << nums.size() << ", l=" << l << ", r=" << r
                  << ": expected " << expected << ", got " << actual
                  << "; input must remain unchanged\n";
        std::exit(EXIT_FAILURE);
    }
}

// Independent oracle: prefix differences, enumerating lengths first.
int oracle(const std::vector<int>& nums, int l, int r) {
    std::vector<int> prefix(nums.size() + 1, 0);
    for (std::size_t i = 0; i < nums.size(); ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    int best = -1;
    for (int length = l; length <= r; ++length) {
        for (int end = length; end <= static_cast<int>(nums.size()); ++end) {
            const int sum = prefix[end] - prefix[end - length];
            if (sum > 0 && (best == -1 || sum < best)) best = sum;
        }
    }
    return best;
}
}  // namespace

void run_tests() {
    check({7}, 1, 1, 7);
    check({0}, 1, 1, -1);
    check({-1000}, 1, 1, -1);
    check({1000}, 1, 1, 1000);
    check({-8, -2, -4}, 1, 3, -1);
    check({0, 0, 0}, 1, 3, -1);
    check({5, -5, 4}, 2, 2, -1); // Zero is not positive.
    check({6, -4, 3}, 2, 3, 2);  // Optimum has length l.
    check({4, -6, 3}, 2, 3, 1);  // Only length r is positive.
    check({1, 8, 9}, 2, 2, 9);   // Ignore a smaller sum below l.
    check({8, 8, -15}, 1, 2, 8); // Ignore sum 1 above r.
    check({-9, 7, -4}, 2, 2, 3); // Last possible starting position.
    check({9, -5, 2}, 3, 3, 6);  // Whole array only.
    check({-3, 0, 2, -1}, 1, 4, 1);
    check(std::vector<int>(100, 1000), 100, 100, 100000);
    check(std::vector<int>(100, -1000), 1, 100, -1);
    check(std::vector<int>(100, 1000), 1, 100, 1000);

    int cases = 0;
    const int values[] = {-2, 0, 3};
    for (int n = 1; n <= 6; ++n) {
        int count = 1;
        for (int i = 0; i < n; ++i) count *= 3;
        for (int code = 0; code < count; ++code) {
            std::vector<int> nums(n);
            int digits = code;
            for (int& value : nums) {
                value = values[digits % 3];
                digits /= 3;
            }
            for (int l = 1; l <= n; ++l) {
                for (int r = l; r <= n; ++r) {
                    check(nums, l, r, oracle(nums, l, r));
                    ++cases;
                }
            }
        }
    }
    std::cout << "minimum positive sum: boundary cases and " << cases
              << " exhaustive comparisons passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
