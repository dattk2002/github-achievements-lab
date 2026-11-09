#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        if (nums.empty()) throw std::invalid_argument("nums must be nonempty");
        int largest = nums.front(), smallest = nums.front(), best = nums.front();
        for (std::size_t i = 1; i < nums.size(); ++i) {
            const int value = nums[i];
            const int from_largest = largest * value;
            const int from_smallest = smallest * value;
            largest = std::max({value, from_largest, from_smallest});
            smallest = std::min({value, from_largest, from_smallest});
            best = std::max(best, largest);
        }
        return best;
    }
};
}  // namespace lab
