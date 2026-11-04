#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace lab {
namespace {
void check(std::vector<int> nums, int x, int k, long long expected) {
    const auto before = nums;
    const auto actual = Solution{}.minOperations(nums, x, k);
    if (actual != expected || nums != before) {
        std::cerr << "n=" << nums.size() << " x=" << x << " k=" << k
                  << " expected=" << expected << " actual=" << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}

// Enumerate all sets of disjoint starts, and all integer targets per window.
// No median data structure or dynamic programming is shared with the solution.
long long brute(const std::vector<int>& a, int x, int left, int start = 0) {
    if (left == 0) return 0;
    long long best = std::numeric_limits<long long>::max() / 4;
    for (int s = start; s + left * x <= static_cast<int>(a.size()); ++s) {
        const auto bounds = std::minmax_element(a.begin() + s, a.begin() + s + x);
        long long cost = std::numeric_limits<long long>::max();
        for (int target = *bounds.first; target <= *bounds.second; ++target) {
            long long candidate = 0;
            for (int j = s; j < s + x; ++j) candidate += std::abs(a[j] - target);
            cost = std::min(cost, candidate);
        }
        best = std::min(best, cost + brute(a, x, left - 1, s + x));
    }
    return best;
}
}  // namespace

void run_tests() {
    check({-4, 7}, 2, 1, 11);  // Minimum n, even median interval.
    check({1, 8, 2}, 3, 1, 7); // Median, not mean or endpoint.
    check({9, 2, 2, 8, 8, -9}, 2, 2, 0); // Skip both ends.
    check({1, 1, 2, 9}, 2, 2, 7); // Cheapest overlapping windows cannot both win.
    check({0, 2, 4, 6, 8, 10}, 2, 3, 6); // k*x == n; adjacency allowed.
    check({-5, -5, -5, -5, -5}, 3, 1, 0);
    check({7, 5, 3, 1, -1}, 3, 1, 4);
    check({-1000000, 1000000}, 2, 1, 2000000);
    std::vector<int> large(100000);
    for (int i = 0; i < 100000; ++i) large[i] = i % 2 ? 1000000 : -1000000;
    check(large, 100000, 1, 100000000000LL);
    check(large, 6000, 15, 90000000000LL);
    check(std::vector<int>(100000, 42), 2, 15, 0);

    int cases = 0;
    for (int n = 2; n <= 8; ++n) {
        int count = 1;
        for (int i = 0; i < n; ++i) count *= 3;
        for (int code = 0; code < count; ++code) {
            int digits = code;
            std::vector<int> a(n);
            for (int& value : a) { value = digits % 3 - 1; digits /= 3; }
            for (int x = 2; x <= n; ++x) {
                for (int k = 1; k * x <= n; ++k) {
                    check(a, x, k, brute(a, x, k));
                    ++cases;
                }
            }
        }
    }
    std::cout << "3505: boundaries and " << cases << " exhaustive cases passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
