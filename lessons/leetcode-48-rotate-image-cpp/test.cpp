#include "lesson.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Build a separate destination by the coordinate mapping, rather than swaps.
Matrix oracle(const Matrix& matrix) {
    const auto n = matrix.size();
    Matrix answer(n, std::vector<int>(n));
    for (std::size_t r = 0; r < n; ++r)
        for (std::size_t c = 0; c < n; ++c) answer[c][n - 1 - r] = matrix[r][c];
    return answer;
}

void check(Matrix matrix) {
    const auto original = matrix;
    const auto expected = oracle(matrix);
    lab::Solution solution;
    solution.rotate(matrix);
    require(matrix == expected, "LC48: clockwise rotation differs");
    for (int turns = 0; turns < 3; ++turns) solution.rotate(matrix);
    require(matrix == original, "LC48: four rotations must restore the image");
}

int main() {
    Matrix fixed{{4, 9}, {-3, 2}};
    lab::Solution{}.rotate(fixed);
    require(fixed == Matrix({{-3, 4}, {2, 9}}), "LC48: fixed clockwise example differs");
    check({});
    check({{INT_MIN}});
    check({{INT_MIN, INT_MAX}, {0, -1}});
    std::size_t cases = 0;
    for (int n = 0; n <= 3; ++n) {
        unsigned possibilities = 1;
        for (int i = 0; i < n * n; ++i) possibilities *= 3;
        for (unsigned code = 0; code < possibilities; ++code) {
            auto rest = code;
            Matrix matrix(n, std::vector<int>(n));
            for (auto& row : matrix) for (int& value : row) {
                value = static_cast<int>(rest % 3) - 1;
                rest /= 3;
            }
            check(matrix);
            ++cases;
        }
    }
    Matrix large(20, std::vector<int>(20));
    for (int r = 0; r < 20; ++r) for (int c = 0; c < 20; ++c) large[r][c] = r * 20 + c;
    check(large);
    for (auto bad : std::vector<Matrix>{{{}}, {{1, 2}}, {{1}, {2}}, {{1, 2}, {3}}, {{}, {1}}}) {
        const auto original = bad;
        bool threw = false;
        try { lab::Solution{}.rotate(bad); }
        catch (const std::invalid_argument&) { threw = true; }
        require(threw && bad == original, "LC48: invalid shape must throw before mutation");
    }
    std::cout << "LC48: fixed, " << cases << " coordinate-oracle, four-turn, invalid and limit cases passed\n";
}
