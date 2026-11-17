#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int jump(std::vector<int>& nums) {
        for (int value : nums)
            if (value < 0) throw std::invalid_argument("jump length must be nonnegative");
        if (nums.empty()) return -1;
        const std::size_t last = nums.size() - 1;
        std::size_t layerEnd = 0, farthest = 0;
        int jumps = 0;
        for (std::size_t i = 0; i < last; ++i) {
            // Clamp the distance before addition to avoid overflowing an index.
            const auto reach = i + std::min(static_cast<std::size_t>(nums[i]), last - i);
            farthest = std::max(farthest, reach);
            if (i == layerEnd) {
                if (farthest == layerEnd) return -1;
                ++jumps;
                layerEnd = farthest;
                if (layerEnd == last) return jumps;
            }
        }
        return jumps;
    }
};
}  // namespace lab
