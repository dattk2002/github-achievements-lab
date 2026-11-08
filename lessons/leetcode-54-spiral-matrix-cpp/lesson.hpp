#pragma once

#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        if (matrix.empty()) {
            return {};
        }
        const std::size_t columns = matrix.front().size();
        for (const auto& row : matrix) {
            if (row.size() != columns) {
                throw std::invalid_argument("Matrix must be rectangular");
            }
        }
        if (columns == 0) {
            return {};
        }
        int top = 0;
        int bottom = static_cast<int>(matrix.size()) - 1;
        int left = 0;
        int right = static_cast<int>(columns) - 1;
        std::vector<int> result;
        result.reserve(matrix.size() * columns);
        while (top <= bottom && left <= right) {
            for (int column = left; column <= right; ++column) {
                result.push_back(matrix[top][column]);
            }
            ++top;
            for (int row = top; row <= bottom; ++row) {
                result.push_back(matrix[row][right]);
            }
            --right;
            if (top <= bottom) {
                for (int column = right; column >= left; --column) {
                    result.push_back(matrix[bottom][column]);
                }
                --bottom;
            }
            if (left <= right) {
                for (int row = bottom; row >= top; --row) {
                    result.push_back(matrix[row][left]);
                }
                ++left;
            }
        }
        return result;
    }
};
}  // namespace lab
