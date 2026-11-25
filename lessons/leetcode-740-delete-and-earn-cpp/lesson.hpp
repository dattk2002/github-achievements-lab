#pragma once
#include <algorithm>
#include <vector>

namespace lab {
class Solution {
public:
    int deleteAndEarn(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        const int maximum = *std::max_element(nums.begin(), nums.end());
        std::vector<int> points(static_cast<std::size_t>(maximum + 1), 0);
        for (int value : nums) points[value] += value;
        int two_back = 0;
        int one_back = 0;
        for (int value = 1; value <= maximum; ++value) {
            const int current = std::max(one_back, two_back + points[value]);
            two_back = one_back;
            one_back = current;
        }
        return one_back;
    }
};
}  // namespace lab
