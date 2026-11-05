#pragma once

#include <numeric>
#include <vector>

namespace lab {
class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        if (nums.empty()) {
            return false;
        }
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % 2 != 0) {
            return false;
        }
        const int target = total / 2;
        std::vector<bool> reachable(static_cast<std::size_t>(target) + 1, false);
        reachable[0] = true;
        for (int value : nums) {
            // Descending sums keep this item from being used more than once.
            for (int sum = target; sum >= value; --sum) {
                reachable[sum] = reachable[sum] || reachable[sum - value];
            }
        }
        return reachable[target];
    }
};
}  // namespace lab
