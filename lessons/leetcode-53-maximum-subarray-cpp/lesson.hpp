#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        if (nums.empty()) {
            throw std::invalid_argument("A nonempty subarray needs a nonempty input");
        }
        int ending_here = nums.front();
        int best = ending_here;
        for (std::size_t i = 1; i < nums.size(); ++i) {
            ending_here = std::max(nums[i], ending_here + nums[i]);
            best = std::max(best, ending_here);
        }
        return best;
    }
};
}  // namespace lab
