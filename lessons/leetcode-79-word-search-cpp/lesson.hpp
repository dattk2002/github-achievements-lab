#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace lab {
class Solution {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        const int rows = static_cast<int>(board.size());
        const int columns = static_cast<int>(board[0].size());
        if (word.size() > board.size() * board[0].size()) return false;
        std::array<int,256> available{}, needed{};
        for (const auto& row : board)
            for (unsigned char symbol : row) ++available[symbol];
        for (unsigned char symbol : word)
            if (++needed[symbol] > available[symbol]) return false;
        if (available[static_cast<unsigned char>(word.front())] >
            available[static_cast<unsigned char>(word.back())])
            std::reverse(word.begin(), word.end());

        std::vector<std::vector<bool>> used(rows, std::vector<bool>(columns, false));
        const auto search = [&](auto&& self, int row, int column, std::size_t index) -> bool {
            if (row < 0 || row >= rows || column < 0 || column >= columns ||
                used[row][column] || board[row][column] != word[index]) return false;
            if (index + 1 == word.size()) return true;
            used[row][column] = true;
            const bool found = self(self, row - 1, column, index + 1) ||
                               self(self, row + 1, column, index + 1) ||
                               self(self, row, column - 1, index + 1) ||
                               self(self, row, column + 1, index + 1);
            used[row][column] = false;
            return found;
        };
        for (int row = 0; row < rows; ++row)
            for (int column = 0; column < columns; ++column)
                if (search(search, row, column, 0)) return true;
        return false;
    }
};
}  // namespace lab
