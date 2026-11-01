#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

namespace lab {
namespace {
void check(std::vector<int> nums, int expected) {
    const auto before = nums;
    Solution solution;
    const int actual = solution.minMoves(nums);
    if (actual != expected || nums != before) {
        std::cerr << "n=" << nums.size() << ": expected " << expected
                  << ", got " << actual << " (input must be preserved)\n";
        std::exit(EXIT_FAILURE);
    }
}

// Simulate legal moves. Translation and permutation preserve distances.
std::vector<int> canonical(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    const int base = nums.front();
    for (int& value : nums) value -= base;
    return nums;
}

int bfs_moves(const std::vector<int>& nums) {
    const auto start = canonical(nums);
    std::queue<std::pair<std::vector<int>, int>> pending;
    std::set<std::vector<int>> visited{start};
    pending.push({start, 0});
    while (!pending.empty()) {
        const auto current = pending.front();
        pending.pop();
        if (current.first.front() == current.first.back()) return current.second;
        for (std::size_t skipped = 0; skipped < nums.size(); ++skipped) {
            auto next = current.first;
            for (std::size_t i = 0; i < next.size(); ++i) {
                if (i != skipped) ++next[i];
            }
            next = canonical(next);
            if (visited.insert(next).second) pending.push({next, current.second + 1});
        }
    }
    std::cerr << "BFS unexpectedly exhausted\n";
    std::exit(EXIT_FAILURE);
}
}  // namespace

void run_tests() {
    check({4, 6, 6}, 4);
    check({-5, -2, 0}, 8);
    check({7, 7, 7, 7}, 0);
    check({-1000000000}, 0);
    check({1000000000}, 0);
    check({-1000000000, 1000000000}, 2000000000);
    check({0, 1000000000, 1000000000, 147483647}, 2147483647);
    check({9, 4, 9, 4}, 10);
    check({2, 8}, 6);
    check(std::vector<int>(100000, 1000000000), 0);
    auto large = std::vector<int>(100000, 1000000000);
    large.back() = 999999999;
    check(large, 99999);
    large.assign(100000, -1000000000);
    large.front() = 1000000000;
    check(large, 2000000000);

    int cases = 0;
    for (int n = 1; n <= 4; ++n) {
        int combinations = 1;
        for (int i = 0; i < n; ++i) combinations *= 4;
        for (int code = 0; code < combinations; ++code) {
            std::vector<int> nums(n);
            int digits = code;
            for (int& value : nums) {
                value = digits % 4 - 1;
                digits /= 4;
            }
            check(nums, bfs_moves(nums));
            ++cases;
        }
    }
    std::cout << "minimum moves: boundary cases and " << cases << " BFS cases passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
