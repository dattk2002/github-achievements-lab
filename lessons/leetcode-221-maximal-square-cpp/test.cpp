#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

using Matrix=std::vector<std::vector<char>>;
int oracle(const Matrix& a) {
    if(a.empty() || a[0].empty()) return 0;
    int best=0;
    for(std::size_t row=0;row<a.size();++row) for(std::size_t col=0;col<a[0].size();++col)
        for(std::size_t side=1;row+side<=a.size() && col+side<=a[0].size();++side) {
            bool filled=true;
            for(std::size_t r=row;r<row+side;++r) for(std::size_t c=col;c<col+side;++c)
                if(a[r][c]!='1') filled=false;
            if(filled && static_cast<int>(side*side)>best) best=static_cast<int>(side*side);
        }
    return best;
}
void check(Matrix a,int expected) {
    const auto original=a;
    require(lab::Solution{}.maximalSquare(a)==expected,"maximal square area differs");
    require(a==original,"matrix input changed");
}
void invalid(Matrix a) {
    const auto original=a;bool threw=false;
    try { (void)lab::Solution{}.maximalSquare(a); } catch(const std::invalid_argument&) { threw=true; }
    require(threw,"ragged matrix must throw");require(a==original,"invalid matrix changed");
}
int main() {
    check({{'1','1','1','0'},{'1','1','1','1'},{'0','1','1','1'},{'0','1','1','1'}},9);
    check({{'1','0'},{'1','1'}},1); check({{'1','1'},{'1','1'}},4);
    check({},0);check({{}},0);check({{},{}},0);
    for(int rows=1;rows<=3;++rows) for(int cols=1;cols<=3;++cols)
        for(unsigned mask=0;mask<(1U<<(rows*cols));++mask) {
            Matrix a(rows,std::vector<char>(cols,'0'));
            for(int i=0;i<rows*cols;++i) if((mask & (1U<<i))!=0) a[i/cols][i%cols]='1';
            check(a,oracle(a));
        }
    check(Matrix(300,std::vector<char>(300,'1')),90000);
    check(Matrix(300,std::vector<char>(300,'0')),0);
    check(Matrix(1,std::vector<char>(300,'1')),1);check(Matrix(300,std::vector<char>(1,'1')),1);
    invalid({{'1'},{}});invalid({{}, {'1'}});
    std::cout << "LC221: fixed, 682 square-oracle, malformed and limit cases passed\n";
}
