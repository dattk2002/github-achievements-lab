#pragma once
#include <cstddef>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) {
        if (heights.empty()) return {};
        const auto width = heights[0].size();
        for (const auto& row : heights)
            if (row.size() != width) throw std::invalid_argument("grid must be rectangular");
        if (width == 0) return {};
        const int rows = static_cast<int>(heights.size());
        const int cols = static_cast<int>(width);
        using Marks = std::vector<std::vector<bool>>;
        const auto fromOcean = [&](bool pacific) {
            Marks seen(rows, std::vector<bool>(cols, false));
            std::queue<std::pair<int, int>> pending;
            const auto add = [&](int r, int c) {
                if (!seen[r][c]) {
                    seen[r][c] = true;
                    pending.emplace(r, c);
                }
            };
            for (int r = 0; r < rows; ++r) add(r, pacific ? 0 : cols - 1);
            for (int c = 0; c < cols; ++c) add(pacific ? 0 : rows - 1, c);
            const int dr[]{-1, 1, 0, 0}, dc[]{0, 0, -1, 1};
            while (!pending.empty()) {
                const auto [r, c] = pending.front();
                pending.pop();
                for (int d = 0; d < 4; ++d) {
                    const int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                    // Reverse a downhill edge: climb to an equal or higher cell.
                    if (heights[nr][nc] >= heights[r][c]) add(nr, nc);
                }
            }
            return seen;
        };
        const Marks pacific = fromOcean(true), atlantic = fromOcean(false);
        std::vector<std::vector<int>> answer;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (pacific[r][c] && atlantic[r][c]) answer.push_back({r, c});
        return answer;
    }
};
}  // namespace lab
