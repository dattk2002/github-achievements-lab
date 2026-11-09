#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

#include <algorithm>
using Grid=std::vector<std::vector<int>>;
int oracle(const Grid& a,std::size_t row=0,std::size_t col=0) {
    if(row+1==a.size() && col+1==a[0].size()) return a[row][col];
    if(row+1==a.size()) return a[row][col]+oracle(a,row,col+1);
    if(col+1==a[0].size()) return a[row][col]+oracle(a,row+1,col);
    return a[row][col]+std::min(oracle(a,row+1,col),oracle(a,row,col+1));
}
void check(Grid a,int expected) {
    const auto original=a;
    require(lab::Solution{}.minPathSum(a)==expected,"minimum path sum differs");
    require(a==original,"grid input changed");
}
void enumerate(Grid& a,std::size_t position) {
    const std::size_t cols=a[0].size();
    if(position==a.size()*cols) { check(a,oracle(a)); return; }
    for(int value:{0,1,4}) { a[position/cols][position%cols]=value; enumerate(a,position+1); }
}
void invalid(Grid a) {
    const auto original=a; bool threw=false;
    try { (void)lab::Solution{}.minPathSum(a); }
    catch(const std::invalid_argument&) { threw=true; }
    require(threw,"malformed grid must throw"); require(a==original,"invalid grid changed");
}
int main() {
    check({{1,7,2},{2,3,4}},10); check({{9}},9);
    check({{0,0},{0,0}},0); check({{2,3,4}},9); check({{2},{3},{4}},9);
    for(int rows=1;rows<=3;++rows) for(int cols=1;cols<=3;++cols) {
        Grid a(rows,std::vector<int>(cols)); enumerate(a,0);
    }
    check(Grid(200,std::vector<int>(200,200)),79800);
    check(Grid(1,std::vector<int>(200,200)),40000);
    check(Grid(200,std::vector<int>(1,200)),40000);
    invalid({}); invalid({{}}); invalid({{1,2},{3}}); invalid({{1},{}});
    std::cout << "LC64: fixed, exhaustive path-oracle, invalid and limit cases passed\n";
}
