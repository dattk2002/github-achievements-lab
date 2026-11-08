#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <stdexcept>
std::vector<int> oracle(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.front().empty()) return {};
    const int rows=static_cast<int>(matrix.size()),columns=static_cast<int>(matrix.front().size());
    std::vector<std::vector<bool>> visited(static_cast<std::size_t>(rows),std::vector<bool>(static_cast<std::size_t>(columns),false));
    const int dr[]{0,1,0,-1},dc[]{1,0,-1,0};int row=0,column=0,direction=0;std::vector<int> result;
    for (int count=0; count<rows*columns; ++count) {
        result.push_back(matrix[row][column]);visited[row][column]=true;
        int nr=row+dr[direction],nc=column+dc[direction];
        if (nr<0 || nr>=rows || nc<0 || nc>=columns || visited[nr][nc]) {
            direction=(direction+1)%4;nr=row+dr[direction];nc=column+dc[direction];
        }
        row=nr;column=nc;
    }
    return result;
}
void verify(std::vector<std::vector<int>> matrix,const std::vector<int>& expected) {
    const auto before=matrix;lab::Solution solution;
    check(solution.spiralOrder(matrix)==expected,"clockwise spiral order");check(matrix==before,"matrix mutated");
}
int main() {
    verify({{2,4,6,8},{10,12,14,16},{18,20,22,24}},{2,4,6,8,16,24,22,20,18,10,12,14});
    verify({},{});verify({{}},{});verify({{},{}},{});verify({{-100,0,100}},{-100,0,100});verify({{3},{2},{1}},{3,2,1});
    for (int rows=1; rows<=10; ++rows) for (int columns=1; columns<=10; ++columns) {
        std::vector<std::vector<int>> matrix(static_cast<std::size_t>(rows),std::vector<int>(static_cast<std::size_t>(columns)));
        for (int row=0; row<rows; ++row) for (int column=0; column<columns; ++column) matrix[row][column]=row*columns+column-50;
        verify(matrix,oracle(matrix));
    }
    for (auto matrix:std::vector<std::vector<std::vector<int>>>{{{1,2},{3}},{{},{1}}}) {
        lab::Solution solution;bool caught=false;
        try {(void)solution.spiralOrder(matrix);} catch(const std::invalid_argument&){caught=true;}
        check(caught,"ragged matrix rejected");
    }
    std::cout << "Spiral matrix: passed\n";
}
