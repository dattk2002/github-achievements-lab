#pragma once
#include <algorithm>
#include <vector>

namespace lab {
class Solution {
public:
    int trap(std::vector<int>& height) {
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int left_max = 0, right_max = 0, water = 0;
        while (left <= right) {
            if (left_max <= right_max) {
                left_max = std::max(left_max, height[left]);
                water += left_max - height[left];
                ++left;
            } else {
                right_max = std::max(right_max, height[right]);
                water += right_max - height[right];
                --right;
            }
        }
        return water;
    }
};
}  // namespace lab
