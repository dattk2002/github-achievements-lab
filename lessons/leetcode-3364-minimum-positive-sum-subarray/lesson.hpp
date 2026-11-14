#pragma once

#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: 1 <= l <= r <= nums.size() <= 100;
    // -1000 <= nums[i] <= 1000. Preserves nums.
    int minimumSumSubarray(std::vector<int>& nums, int l, int r) {
        const int n = static_cast<int>(nums.size());
        int best = -1;
        for (int start = 0; start < n; ++start) {
            int sum = 0;
            for (int length = 1; length <= r && start + length <= n; ++length) {
                sum += nums[start + length - 1];
                if (length >= l && sum > 0 && (best == -1 || sum < best)) {
                    best = sum;
                }
            }
        }
        return best;
    }
};
}  // namespace lab
