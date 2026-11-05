#pragma once

#include <algorithm>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        auto sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        std::vector<std::vector<int>> result;
        for (std::size_t i = 0; i + 2 < sorted.size(); ++i) {
            if (i > 0 && sorted[i] == sorted[i - 1]) {
                continue;
            }
            std::size_t left = i + 1;
            std::size_t right = sorted.size() - 1;
            while (left < right) {
                const int sum = sorted[i] + sorted[left] + sorted[right];
                if (sum < 0) {
                    ++left;
                } else if (sum > 0) {
                    --right;
                } else {
                    result.push_back({sorted[i], sorted[left], sorted[right]});
                    const int left_value = sorted[left];
                    const int right_value = sorted[right];
                    while (left < right && sorted[left] == left_value) {
                        ++left;
                    }
                    while (left < right && sorted[right] == right_value) {
                        --right;
                    }
                }
            }
        }
        return result;
    }
};
}  // namespace lab
