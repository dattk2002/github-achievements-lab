#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid.front().empty())
            throw std::invalid_argument("grid must be nonempty");
        const std::size_t columns = grid.front().size();
        for (const auto& row : grid)
            if (row.size() != columns)
                throw std::invalid_argument("grid must be rectangular");
        std::vector<int> cost(columns);
        cost[0] = grid[0][0];
        for (std::size_t col = 1; col < columns; ++col)
            cost[col] = cost[col-1] + grid[0][col];
        for (std::size_t row = 1; row < grid.size(); ++row) {
            cost[0] += grid[row][0];
            for (std::size_t col = 1; col < columns; ++col)
                cost[col] = std::min(cost[col], cost[col-1]) + grid[row][col];
        }
        return cost.back();
    }
};
}  // namespace lab
