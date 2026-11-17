#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        const auto n = matrix.size();
        for (const auto& row : matrix)
            if (row.size() != n) throw std::invalid_argument("matrix must be square");
        for (std::size_t r = 0; r < n; ++r)
            for (std::size_t c = r + 1; c < n; ++c) std::swap(matrix[r][c], matrix[c][r]);
        for (auto& row : matrix) std::reverse(row.begin(), row.end());
    }
};
}  // namespace lab
