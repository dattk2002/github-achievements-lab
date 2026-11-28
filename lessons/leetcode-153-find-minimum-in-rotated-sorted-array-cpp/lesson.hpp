#pragma once
#include <cstddef>
#include <vector>

namespace lab {
class Solution {
public:
    int findMin(std::vector<int>& nums) {
        std::size_t left = 0, right = nums.size() - 1;
        while (left < right) {
            const auto middle = left + (right - left) / 2;
            if (nums[middle] > nums[right]) left = middle + 1;
            else right = middle;
        }
        return nums[left];
    }
};
}  // namespace lab
