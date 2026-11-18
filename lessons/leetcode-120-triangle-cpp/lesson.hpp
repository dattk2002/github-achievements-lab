#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int minimumTotal(std::vector<std::vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        for (std::size_t row = 0; row < triangle.size(); ++row)
            if (triangle[row].size() != row + 1)
                throw std::invalid_argument("row r must contain r+1 values");
        auto best = triangle.back();
        for (std::size_t row = triangle.size() - 1; row > 0; --row)
            for (std::size_t col = 0; col < row; ++col)
                best[col] = triangle[row - 1][col] + std::min(best[col], best[col + 1]);
        return best.front();
    }
};
}  // namespace lab
