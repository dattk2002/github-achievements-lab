#pragma once

#include <functional>
#include <queue>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        if (k <= 0 || static_cast<std::size_t>(k) > nums.size()) {
            throw std::out_of_range("Rank must be between one and the input size");
        }
        std::priority_queue<int, std::vector<int>, std::greater<int>> largest;
        const auto rank = static_cast<std::size_t>(k);
        for (int value : nums) {
            if (largest.size() < rank) {
                largest.push(value);
            } else if (value > largest.top()) {
                largest.pop();
                largest.push(value);
            }
        }
        return largest.top();
    }
};
}  // namespace lab
