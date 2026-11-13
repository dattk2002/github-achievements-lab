#pragma once

#include <deque>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: 1 <= size <= 100000, 1 <= nums[i], k <= 1000000000.
    // The input is preserved. All costs and counts use 64-bit arithmetic.
    long long countNonDecreasingSubarrays(std::vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());
        std::deque<int> blocks;
        int right = n - 1;
        long long cost = 0;
        long long answer = 0;
        for (int left = n - 1; left >= 0; --left) {
            // Raise each smaller leading plateau to the new prefix maximum.
            while (!blocks.empty() && nums[blocks.front()] < nums[left]) {
                const int start = blocks.front();
                blocks.pop_front();
                const int end = blocks.empty() ? right + 1 : blocks.front();
                cost += 1LL * (end - start) * (nums[left] - nums[start]);
            }
            blocks.push_front(left);
            while (cost > k) {
                cost -= static_cast<long long>(nums[blocks.back()]) - nums[right];
                if (blocks.back() == right) blocks.pop_back();
                --right;
            }
            answer += right - left + 1LL;
        }
        return answer;
    }
};
}  // namespace lab
