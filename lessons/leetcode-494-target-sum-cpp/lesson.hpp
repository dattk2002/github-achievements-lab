#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        if (nums.size() > 20) throw std::invalid_argument("at most 20 positions are supported");
        long long total = 0;
        for (int value : nums) {
            if (value < 0) throw std::invalid_argument("values must be nonnegative");
            total += value;
        }
        if (total > 1000) throw std::invalid_argument("sum must not exceed 1000");
        if (target < -total || target > total || (total + target) % 2 != 0) return 0;
        const int goal = static_cast<int>((total + target) / 2);
        std::vector<int> ways(static_cast<std::size_t>(goal) + 1, 0);
        ways[0] = 1;
        for (int value : nums) {
            // Descending sums use this POSITION once; a zero doubles every count.
            for (int sum = goal; sum >= value; --sum) ways[sum] += ways[sum - value];
        }
        return ways[goal];
    }
};
}  // namespace lab
