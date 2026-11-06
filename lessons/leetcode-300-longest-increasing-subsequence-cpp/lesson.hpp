#pragma once

#include <algorithm>
#include <vector>

namespace lab {
class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        std::vector<int> tails;
        for (int value : nums) {
            const auto position = std::lower_bound(tails.begin(), tails.end(), value);
            if (position == tails.end()) {
                tails.push_back(value);
            } else {
                *position = value;
            }
        }
        return static_cast<int>(tails.size());
    }
};
}  // namespace lab
