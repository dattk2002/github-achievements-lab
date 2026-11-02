#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: LeetCode 462 input bounds, nonempty nums, int32 result.
    // Preserve nums; sort a copy to obtain a median.
    int minMoves2(std::vector<int>& nums) {
        auto sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        const int median = sorted[sorted.size() / 2];
        std::int64_t moves = 0;
        for (int value : sorted) {
            const auto difference = static_cast<std::int64_t>(value) - median;
            moves += difference < 0 ? -difference : difference;
        }
        return static_cast<int>(moves);
    }
};
}  // namespace lab
