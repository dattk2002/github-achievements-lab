#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<int> countBits(int n) {
        if (n < 0) throw std::invalid_argument("n must be nonnegative");
        std::vector<int> counts(static_cast<std::size_t>(n) + 1, 0);
        for (std::size_t i = 1; i < counts.size(); ++i)
            counts[i] = counts[i >> 1] + static_cast<int>(i & 1U);
        return counts;
    }
};
}  // namespace lab
