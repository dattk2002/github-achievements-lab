#pragma once
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace lab {
// Contract: target > 0, nums contains positive integers, sum fits int64_t.
inline std::size_t min_subarray_len(std::int64_t target, const std::vector<int>& nums) {
    std::size_t left = 0;
    std::size_t best = nums.size() + 1;
    std::int64_t sum = 0;
    for (std::size_t right = 0; right < nums.size(); ++right) {
        sum += nums[right];
        while (sum >= target) {
            best = std::min(best, right - left + 1);
            sum -= nums[left++];
        }
    }
    return best > nums.size() ? 0 : best;
}
}
