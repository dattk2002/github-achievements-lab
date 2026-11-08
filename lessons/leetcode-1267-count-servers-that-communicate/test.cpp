#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace lab {
namespace {
using Grid = std::vector<std::vector<int>>;

void check(const std::string& name, Grid grid, int expected) {
    const Grid original = grid;
    Solution solution;
    const int actual = solution.countServers(grid);
    if (actual != expected || grid != original) {
        std::cerr << name << ": expected " << expected << ", got " << actual
                  << " (input must remain unchanged)\n";
        std::exit(EXIT_FAILURE);
    }
}

// Compare distinct server pairs directly, without row/column totals.
int pairwise_count(const Grid& grid) {
    std::vector<std::pair<int, int>> servers;
    for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
        for (int c = 0; c < static_cast<int>(grid[r].size()); ++c) {
            if (grid[r][c] == 1) servers.emplace_back(r, c);
        }
    }
    std::vector<bool> communicates(servers.size(), false);
    for (std::size_t a = 0; a < servers.size(); ++a) {
        for (std::size_t b = a + 1; b < servers.size(); ++b) {
            if (servers[a].first == servers[b].first ||
                servers[a].second == servers[b].second) {
                communicates[a] = communicates[b] = true;
            }
        }
    }
    int result = 0;
    for (bool connected : communicates) result += connected;
    return result;
}
}  // namespace

void run_tests() {
    check("row with gaps", {{1, 0, 0, 1, 1}}, 3);
    check("empty cell", {{0}}, 0);
    check("single server", {{1}}, 0);
    check("single column with gaps", {{1}, {0}, {1}, {0}}, 2);
    check("isolated diagonal", {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, 0);
    check("count intersection once", {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, 5);
    check("pair plus isolated server", {{1, 0, 1, 0}, {0, 1, 0, 0}}, 2);
    check("shared solution has no stale state", {{0, 0, 0}, {0, 0, 0}}, 0);
    check("maximum empty grid", Grid(250, std::vector<int>(250, 0)), 0);
    check("maximum full grid", Grid(250, std::vector<int>(250, 1)), 62500);
    Grid diagonal(250, std::vector<int>(250, 0));
    for (int i = 0; i < 250; ++i) diagonal[i][i] = 1;
    check("maximum isolated diagonal", diagonal, 0);
    check("maximum width", Grid(1, std::vector<int>(250, 1)), 250);
    check("maximum height", Grid(250, std::vector<int>(1, 1)), 250);

    Solution reused;
    Grid pair{{1, 0, 1}};
    Grid lone{{1}};
    if (reused.countServers(pair) != 2 || reused.countServers(lone) != 0) {
        std::cerr << "repeated calls retained state\n";
        std::exit(EXIT_FAILURE);
    }

    int cases = 0;
    for (int rows = 1; rows <= 3; ++rows) {
        for (int cols = 1; cols <= 4; ++cols) {
            for (int mask = 0; mask < (1 << (rows * cols)); ++mask) {
                Grid grid(rows, std::vector<int>(cols));
                for (int i = 0; i < rows * cols; ++i) {
                    grid[i / cols][i % cols] = (mask >> i) & 1;
                }
                check("exhaustive " + std::to_string(rows) + "x" +
                          std::to_string(cols) + " mask=" + std::to_string(mask),
                      grid, pairwise_count(grid));
                ++cases;
            }
        }
    }
    std::cout << "count servers: boundary cases and " << cases
              << " exhaustive grids passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
