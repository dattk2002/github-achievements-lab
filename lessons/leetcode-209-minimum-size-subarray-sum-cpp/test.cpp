#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

static void check(std::int64_t target, const std::vector<int>& nums, std::size_t expected) {
    const auto before = nums;
    const auto actual = lab::min_subarray_len(target, nums);
    if (actual != expected || nums != before) {
        std::cerr << "target=" << target << ": expected " << expected << ", got " << actual << '\n';
        std::exit(1);
    }
}

static std::size_t oracle(std::int64_t target, const std::vector<int>& nums) {
    std::size_t best = nums.size() + 1;
    for (std::size_t begin = 0; begin < nums.size(); ++begin) {
        std::int64_t sum = 0;
        for (std::size_t end = begin; end < nums.size(); ++end) {
            sum += nums[end];
            if (sum >= target) best = std::min(best, end - begin + 1);
        }
    }
    return best > nums.size() ? 0 : best;
}

int main() {
    check(9, {2, 1, 5, 2, 8}, 2);
    check(8, {2, 1, 5, 2, 8}, 1);
    check(6, {2, 2, 2}, 3);
    check(7, {2, 2, 2}, 0);
    check(1, {}, 0);
    check(1, {1}, 1);
    check(2, {1}, 0);
    std::mt19937 rng(209);
    for (int trial = 0; trial < 2000; ++trial) {
        std::vector<int> nums(rng() % 25);
        for (auto& value : nums) value = 1 + static_cast<int>(rng() % 20);
        const auto target = 1 + static_cast<std::int64_t>(rng() % 300);
        check(target, nums, oracle(target, nums));
    }
    check(100000, std::vector<int>(100000, 1), 100000);
    check(100001, std::vector<int>(100000, 1), 0);
    check(3000000000LL, std::vector<int>(100000, 100000), 30000);
    std::cout << "minimum size subarray: all cases passed (2000 random arrays)\n";
}
