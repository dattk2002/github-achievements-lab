#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: nonempty input under LeetCode 453 constraints;
    // the result fits a signed 32-bit integer. Does not modify nums.
    int minMoves(std::vector<int>& nums) {
        const int minimum = *std::min_element(nums.begin(), nums.end());
        std::int64_t moves = 0;
        for (int value : nums) {
            moves += static_cast<std::int64_t>(value) - minimum;
        }
        return static_cast<int>(moves);
    }
};
}  // namespace lab
