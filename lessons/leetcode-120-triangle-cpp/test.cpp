#include "lesson.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& why) {
    if (!ok) { std::cerr << why << '\n'; std::exit(EXIT_FAILURE); }
}
template<class Error, class F> void throws(F operation) {
    bool caught = false;
    try { operation(); } catch (const Error&) { caught = true; }
    require(caught, "expected exception missing");
}

using Triangle=std::vector<std::vector<int>>;
int oracle(const Triangle& a, std::size_t row=0, std::size_t col=0) {
    if (row==a.size()) return 0;
    return a[row][col]+std::min(oracle(a,row+1,col),oracle(a,row+1,col+1));
}
void check(Triangle a,int expected) {
    const auto before=a;
    require(lab::Solution{}.minimumTotal(a)==expected,"triangle path sum differs");
    require(a==before,"triangle input changed");
}
int main() {
    check({{5},{9,2},{1,-4,8}},3); check({{-7}},-7); check({},0);
    check({{1},{2,2},{3,3,3}},6);
    check({{0},{-1,2},{4,-5,1},{8,3,-2,7}},-8);
    std::mt19937 rng(120);
    for (int height=1; height<=9; ++height) for (int trial=0; trial<120; ++trial) {
        Triangle a;
        for (int r=0;r<height;++r) {
            std::vector<int> row(r+1);
            for (auto& value:row) value=static_cast<int>(rng()%21)-10;
            a.push_back(row);
        }
        check(a,oracle(a));
    }
    for (int value: {-10000,10000}) {
        Triangle a;
        for (int r=0;r<200;++r) a.emplace_back(r+1,value);
        check(a,200*value);
    }
    for (Triangle a: std::vector<Triangle>{{{}},{{1},{2}},{{1,2}},{{1},{2,3},{4,5}}}) {
        const auto before=a;
        throws<std::invalid_argument>([&] { (void)lab::Solution{}.minimumTotal(a); });
        require(a==before,"invalid triangle input changed");
    }
    std::cout << "LC120: fixed, 1080 recursive-oracle, shape and limit cases passed\n";
}
