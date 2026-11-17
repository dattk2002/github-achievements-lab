#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        for (int jump : nums)
            if (jump < 0) throw std::invalid_argument("jump length must be nonnegative");
        if (nums.empty()) return false;
        const std::size_t last = nums.size() - 1;
        std::size_t farthest = 0;
        for (std::size_t i = 0; i <= farthest; ++i) {
            const auto jump = static_cast<std::size_t>(nums[i]);
            // Compare distances before adding, so even a huge jump cannot overflow.
            if (jump >= last - i) return true;
            farthest = std::max(farthest, i + jump);
        }
        return false;
    }
};
}  // namespace lab
