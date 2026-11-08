#pragma once

#include <cstddef>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: rectangular binary grid, 1 <= rows, cols <= 250.
    // Preserves grid; counts each communicating server exactly once.
    int countServers(std::vector<std::vector<int>>& grid) {
        const std::size_t rows = grid.size();
        const std::size_t cols = grid.front().size();
        std::vector<int> row_count(rows, 0);
        std::vector<int> col_count(cols, 0);
        for (std::size_t r = 0; r < rows; ++r) {
            for (std::size_t c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    ++row_count[r];
                    ++col_count[c];
                }
            }
        }
        int result = 0;
        for (std::size_t r = 0; r < rows; ++r) {
            for (std::size_t c = 0; c < cols; ++c) {
                if (grid[r][c] == 1 && (row_count[r] > 1 || col_count[c] > 1)) {
                    ++result;
                }
            }
        }
        return result;
    }
};
}  // namespace lab
