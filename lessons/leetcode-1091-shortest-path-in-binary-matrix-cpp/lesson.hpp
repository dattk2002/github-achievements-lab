#pragma once
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid) {
        if (grid.empty()) return -1;
        for (const auto& row : grid) {
            if (row.size() != grid.size()) throw std::invalid_argument("grid must be square");
            for (int value : row)
                if (value != 0 && value != 1) throw std::invalid_argument("grid must be binary");
        }
        if (grid[0][0] != 0 || grid.back().back() != 0) return -1;
        const int n = static_cast<int>(grid.size());
        std::vector<std::vector<int>> distance(n, std::vector<int>(n, -1));
        std::queue<std::pair<int, int>> pending;
        distance[0][0] = 1;
        pending.emplace(0, 0);
        while (!pending.empty()) {
            const auto [r, c] = pending.front();
            pending.pop();
            if (r == n - 1 && c == n - 1) return distance[r][c];
            for (int dr = -1; dr <= 1; ++dr) for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) continue;
                const int nr = r + dr, nc = c + dc;
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if (grid[nr][nc] != 0 || distance[nr][nc] != -1) continue;
                distance[nr][nc] = distance[r][c] + 1;
                pending.emplace(nr, nc);
            }
        }
        return -1;
    }
};
}  // namespace lab
