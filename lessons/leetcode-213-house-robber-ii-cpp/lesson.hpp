#pragma once
#include <algorithm>
#include <cstddef>
#include <vector>

namespace lab {
class Solution {
    static int linear(const std::vector<int>& values, std::size_t begin, std::size_t end) {
        int two_back = 0;
        int one_back = 0;
        for (std::size_t i = begin; i < end; ++i) {
            const int current = std::max(one_back, two_back + values[i]);
            two_back = one_back;
            one_back = current;
        }
        return one_back;
    }
public:
    int rob(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums.front();
        return std::max(linear(nums, 0, nums.size() - 1), linear(nums, 1, nums.size()));
    }
};
}  // namespace lab
