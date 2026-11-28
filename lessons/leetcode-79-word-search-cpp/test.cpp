#include "lesson.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
// Breadth-by-length enumeration of explicit path masks, independent of DFS.
bool oracle(const std::vector<std::vector<char>>& board, const std::string& word) {
    const int rows = static_cast<int>(board.size());
    const int columns = static_cast<int>(board[0].size());
    struct Path { int end; std::uint64_t mask; };
    std::vector<Path> frontier;
    for (int p = 0; p < rows * columns; ++p)
        if (board[p / columns][p % columns] == word[0]) frontier.push_back({p, 1ULL << p});
    for (std::size_t length = 1; length < word.size(); ++length) {
        std::vector<Path> next;
        for (const auto& path : frontier) {
            for (int p = 0; p < rows * columns; ++p) {
                const int dr = std::abs(p / columns - path.end / columns);
                const int dc = std::abs(p % columns - path.end % columns);
                if (dr + dc == 1 && !(path.mask & (1ULL << p)) &&
                    board[p / columns][p % columns] == word[length])
                    next.push_back({p, path.mask | (1ULL << p)});
            }
        }
        frontier = std::move(next);
    }
    return !frontier.empty();
}
void check(std::vector<std::vector<char>> board, const std::string& word, bool expected) {
    const auto before = board;
    lab::Solution reused;
    require(reused.exist(board, word) == expected, "word existence differs from path oracle");
    require(board == before, "board changed after search");
    require(reused.exist(board, word) == expected && board == before, "state leaked on repeated call");
}
int main() {
    check({{'C','A','T'},{'R','R','E'}}, "CATER", true);
    check({{'A','B'}}, "ABA", false);
    check({{'A','X'},{'X','B'}}, "AB", false);
    check({{'a'}}, "A", false);
    check({{'a'}}, "a", true);
    check({{'A','A','B'},{'A','A','C'}}, "AAAABC", true);
    unsigned checked = 0;
    for (int rows = 1; rows <= 2; ++rows) {
        for (int columns = 1; columns <= 3; ++columns) {
            const int cells = rows * columns;
            for (unsigned code = 0; code < (1u << cells); ++code) {
                std::vector<std::vector<char>> board(rows, std::vector<char>(columns));
                for (int p = 0; p < cells; ++p) board[p / columns][p % columns] = (code & (1u << p)) ? 'A' : 'B';
                for (int length = 1; length <= 6; ++length) {
                    for (unsigned mask = 0; mask < (1u << length); ++mask) {
                        std::string word;
                        for (int p = 0; p < length; ++p) word += (mask & (1u << p)) ? 'A' : 'B';
                        check(board, word, oracle(board, word)); ++checked;
                    }
                }
            }
        }
    }
    std::vector<std::vector<char>> large(6, std::vector<char>(6,'A'));
    check(large, std::string(15, 'A'), true);
    check(large, std::string(14, 'A') + 'B', false);
    std::cout << "LC79: " << checked << " exhaustive board/word pairs and boundaries passed\n";
}
