#pragma once
#include <algorithm>
#include <cstddef>
#include <vector>

namespace lab {
class Solution {
public:
    int maxArea(std::vector<int>& height) {
        if (height.size() < 2) return 0;
        std::size_t left = 0, right = height.size() - 1;
        int best = 0;
        while (left < right) {
            const int width = static_cast<int>(right - left);
            best = std::max(best, width * std::min(height[left], height[right]));
            if (height[left] <= height[right]) ++left;
            else --right;
        }
        return best;
    }
};
}  // namespace lab
