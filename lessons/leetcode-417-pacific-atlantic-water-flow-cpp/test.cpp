#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Independently follow water downhill from EACH cell to the ocean borders.
Matrix oracle(const Matrix& heights) {
    Matrix answer;
    if (heights.empty() || heights[0].empty()) return answer;
    const int rows = static_cast<int>(heights.size());
    const int cols = static_cast<int>(heights[0].size());
    const int dr[]{-1, 1, 0, 0}, dc[]{0, 0, -1, 1};
    for (int r = 0; r < rows; ++r) for (int c = 0; c < cols; ++c) {
        std::queue<std::pair<int, int>> pending;
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        pending.emplace(r, c);
        visited[r][c] = true;
        bool pacific = false, atlantic = false;
        while (!pending.empty()) {
            const auto [row, col] = pending.front();
            pending.pop();
            pacific = pacific || row == 0 || col == 0;
            atlantic = atlantic || row == rows - 1 || col == cols - 1;
            for (int d = 0; d < 4; ++d) {
                const int nr = row + dr[d], nc = col + dc[d];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || visited[nr][nc]) continue;
                if (heights[nr][nc] > heights[row][col]) continue;
                visited[nr][nc] = true;
                pending.emplace(nr, nc);
            }
        }
        if (pacific && atlantic) answer.push_back({r, c});
    }
    return answer;
}

void check(Matrix heights, Matrix expected) {
    const auto original = heights;
    auto result = lab::Solution{}.pacificAtlantic(heights);
    require(heights == original, "LC417: input changed");
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    require(result == expected, "LC417: ocean reachability differs or duplicate coordinate");
}

int main() {
    check({{1, 2}, {4, 3}}, {{0, 1}, {1, 0}, {1, 1}});
    check({{7, 7, 7}, {7, 7, 7}}, {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}});
    check({{9}}, {{0, 0}});
    check({{9, 0, 5, 1}}, {{0, 0}, {0, 1}, {0, 2}, {0, 3}});
    check({{9}, {0}, {5}}, {{0, 0}, {1, 0}, {2, 0}});
    check({}, {});
    check({{}, {}}, {});
    std::size_t cases = 0;
    for (int rows = 1; rows <= 3; ++rows) for (int cols = 1; cols <= 3; ++cols) {
        unsigned possibilities = 1;
        for (int i = 0; i < rows * cols; ++i) possibilities *= 3;
        for (unsigned code = 0; code < possibilities; ++code) {
            auto rest = code;
            Matrix heights(rows, std::vector<int>(cols));
            for (auto& row : heights) for (int& value : row) {
                value = static_cast<int>(rest % 3);
                rest /= 3;
            }
            check(heights, oracle(heights));
            ++cases;
        }
    }
    Matrix plateau(200, std::vector<int>(200, 100000)), all;
    for (int r = 0; r < 200; ++r) for (int c = 0; c < 200; ++c) all.push_back({r, c});
    check(plateau, all);
    Matrix slope(200, std::vector<int>(200)), edge;
    for (int r = 0; r < 200; ++r) for (int c = 0; c < 200; ++c) {
        slope[r][c] = r + c;
        if (r == 199 || c == 199) edge.push_back({r, c});
    }
    check(slope, edge);
    for (auto bad : std::vector<Matrix>{{{1}, {}}, {{}, {1}}}) {
        const auto original = bad;
        bool threw = false;
        try { (void)lab::Solution{}.pacificAtlantic(bad); }
        catch (const std::invalid_argument&) { threw = true; }
        require(threw && bad == original, "LC417: ragged grid must throw without mutation");
    }
    std::cout << "LC417: fixed, " << cases << " downhill-oracle, malformed and limit cases passed\n";
}
