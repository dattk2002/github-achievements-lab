#pragma once

#include <algorithm>
#include <vector>

namespace lab {
class Solution {
public:
    int rob(std::vector<int>& nums) {
        int two_back = 0;
        int previous = 0;
        for (int value : nums) {
            const int current = std::max(previous, two_back + value);
            two_back = previous;
            previous = current;
        }
        return previous;
    }
};
}  // namespace lab
