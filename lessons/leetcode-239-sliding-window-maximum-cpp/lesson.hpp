#pragma once
#include <cstddef>
#include <deque>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        if (k < 1 || static_cast<std::size_t>(k) > nums.size())
            throw std::invalid_argument("window size must be in [1, nums.size()]");
        const auto width = static_cast<std::size_t>(k);
        std::deque<std::size_t> candidates;
        std::vector<int> result;
        result.reserve(nums.size() - width + 1);
        for (std::size_t i = 0; i < nums.size(); ++i) {
            while (!candidates.empty() && candidates.front() + width <= i)
                candidates.pop_front();
            while (!candidates.empty() && nums[candidates.back()] <= nums[i])
                candidates.pop_back();
            candidates.push_back(i);
            if (i + 1 >= width) result.push_back(nums[candidates.front()]);
        }
        return result;
    }
};
}  // namespace lab
