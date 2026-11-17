#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Floyd-Warshall on an explicit eight-neighbor graph, independent of BFS.
int oracle(const Matrix& grid) {
    if (grid.empty() || grid[0][0] != 0 || grid.back().back() != 0) return -1;
    const int n = static_cast<int>(grid.size()), count = n * n, infinity = 10000;
    Matrix distance(count, std::vector<int>(count, infinity));
    for (int r = 0; r < n; ++r) for (int c = 0; c < n; ++c) {
        if (grid[r][c] != 0) continue;
        const int u = r * n + c;
        distance[u][u] = 0;
        for (int nr = 0; nr < n; ++nr) for (int nc = 0; nc < n; ++nc) {
            if (grid[nr][nc] != 0 || (nr == r && nc == c)) continue;
            if (std::abs(nr - r) <= 1 && std::abs(nc - c) <= 1) distance[u][nr * n + nc] = 1;
        }
    }
    for (int k = 0; k < count; ++k) for (int i = 0; i < count; ++i)
        for (int j = 0; j < count; ++j)
            distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);
    return distance[0][count - 1] == infinity ? -1 : distance[0][count - 1] + 1;
}

void check(Matrix grid, int expected) {
    const auto original = grid;
    require(lab::Solution{}.shortestPathBinaryMatrix(grid) == expected, "LC1091: shortest cell count differs");
    require(grid == original, "LC1091: input changed");
}

int main() {
    check({{0, 1, 1}, {0, 0, 1}, {1, 0, 0}}, 3);
    check({{0, 1}, {1, 0}}, 2);
    check({{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}}, 6);
    check({{0}}, 1);
    check({{1}}, -1);
    check({}, -1);
    check({{0, 1, 1}, {1, 1, 1}, {1, 1, 0}}, -1);
    std::size_t cases = 0;
    for (int n = 1; n <= 3; ++n) {
        for (unsigned mask = 0; mask < (1U << (n * n)); ++mask) {
            Matrix grid(n, std::vector<int>(n));
            for (int i = 0; i < n * n; ++i) grid[i / n][i % n] = static_cast<int>((mask >> i) & 1U);
            check(grid, oracle(grid));
            ++cases;
        }
    }
    check(Matrix(100, std::vector<int>(100, 0)), 100);
    Matrix wall(100, std::vector<int>(100, 0));
    std::fill(wall[50].begin(), wall[50].end(), 1);
    check(wall, -1);
    for (auto bad : std::vector<Matrix>{{{}}, {{0, 0}}, {{0}, {0}}, {{0, 0}, {0}}, {{1, 0}, {0, 2}}, {{0, -1}, {0, 0}}}) {
        const auto original = bad;
        bool threw = false;
        try { (void)lab::Solution{}.shortestPathBinaryMatrix(bad); }
        catch (const std::invalid_argument&) { threw = true; }
        require(threw && bad == original, "LC1091: invalid grid must throw before mutation or early exit");
    }
    std::cout << "LC1091: fixed, " << cases << " Floyd-Warshall oracle, diagonal, invalid and limit cases passed\n";
}
