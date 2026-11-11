#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        const std::size_t columns = matrix.front().size();
        for (const auto& row : matrix)
            if (row.size() != columns)
                throw std::invalid_argument("matrix must be rectangular");
        std::vector<int> side(columns + 1, 0);
        int best = 0;
        for (const auto& row : matrix) {
            int diagonal = 0;
            for (std::size_t col = 1; col <= columns; ++col) {
                const int above = side[col];
                side[col] = row[col-1] == '1'
                    ? 1 + std::min({above, side[col-1], diagonal}) : 0;
                best = std::max(best, side[col]);
                diagonal = above;
            }
        }
        return best * best;
    }
};
}  // namespace lab
