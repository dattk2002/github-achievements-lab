#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace lab {
namespace {
void check(std::vector<int> nums, int k, long long expected) {
    const auto original = nums;
    const long long actual = Solution{}.countNonDecreasingSubarrays(nums, k);
    if (actual != expected || nums != original) {
        std::cerr << "n=" << nums.size() << ", k=" << k
                  << ": expected " << expected << ", got " << actual
                  << "; input preserved=" << (nums == original) << '\n';
        std::exit(EXIT_FAILURE);
    }
}

// Independently scan every subarray, without a deque or sliding window.
long long oracle(const std::vector<int>& nums, int k) {
    long long answer = 0;
    for (std::size_t left = 0; left < nums.size(); ++left) {
        int maximum = nums[left];
        long long cost = 0;
        for (std::size_t right = left; right < nums.size(); ++right) {
            maximum = std::max(maximum, nums[right]);
            cost += static_cast<long long>(maximum) - nums[right];
            if (cost <= k) ++answer;
        }
    }
    return answer;
}
}  // namespace

void run_tests() {
    check({1}, 1, 1);
    check({1000000000}, 1000000000, 1);
    check({1, 2, 2, 5}, 1, 10);
    check({7, 7, 7, 7}, 1, 10);
    check({5, 2, 4}, 2, 4);  // Only [5,2] and the full array fail.
    check({5, 2, 4}, 3, 5);  // Exact budget accepts [5,2].
    check({5, 2, 4}, 4, 6);  // Full array costs 3+1.
    check({4, 3, 2, 1}, 1, 7); // Only singles and adjacent pairs.
    check({1000000000, 1, 1}, 1000000000, 5);
    check({2, 1, 2, 1}, 1, 9); // Only the full array costs two.

    int cases = 0;
    for (int n = 1; n <= 7; ++n) {
        int configurations = 1;
        for (int i = 0; i < n; ++i) configurations *= 3;
        for (int code = 0; code < configurations; ++code) {
            std::vector<int> nums(n);
            int digits = code;
            for (int& value : nums) {
                value = 1 + digits % 3;
                digits /= 3;
            }
            for (int k = 1; k <= 12; ++k) {
                check(nums, k, oracle(nums, k));
                ++cases;
            }
        }
    }

    constexpr int n = 100000;
    check(std::vector<int>(n, 1000000000), 1, 5000050000LL);
    std::vector<int> increasing(n), decreasing(n);
    for (int i = 0; i < n; ++i) {
        increasing[i] = i + 1;
        decreasing[i] = n - i;
    }
    check(increasing, 1, 5000050000LL);
    check(decreasing, 1, 199999);
    // A descending-by-one segment of length t needs t*(t-1)/2 increments.
    long long longest = 1;
    while ((longest + 1) * longest / 2 <= 1000000000LL) ++longest;
    check(decreasing, 1000000000,
          longest * (n + 1LL) - longest * (longest + 1) / 2);
    std::vector<int> spike(n, 1);
    spike[0] = 1000000000;
    check(spike, 1000000000, 4999950002LL);
    std::cout << "3420: boundary/large cases and " << cases
              << " exhaustive comparisons passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
