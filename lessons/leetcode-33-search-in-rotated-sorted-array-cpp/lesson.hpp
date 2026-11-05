#pragma once

#include <vector>

namespace lab {
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        while (left <= right) {
            const int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                return middle;
            }
            if (nums[left] <= nums[middle]) {
                if (nums[left] <= target && target < nums[middle]) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            } else {
                if (nums[middle] < target && target <= nums[right]) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            }
        }
        return -1;
    }
};
}  // namespace lab
