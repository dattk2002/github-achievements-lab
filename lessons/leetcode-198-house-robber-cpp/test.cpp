#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
int oracle(const std::vector<int>& values) {
    int best=0;
    for (unsigned mask=0; mask<(1U<<values.size()); ++mask) {
        if ((mask & (mask<<1U))!=0) continue;
        int sum=0;
        for (std::size_t i=0; i<values.size(); ++i) if ((mask>>i)&1U) sum+=values[i];
        best=std::max(best,sum);
    }
    return best;
}
void verify(std::vector<int> values, int expected) {
    const auto before=values;
    lab::Solution solution;
    check(solution.rob(values)==expected,"nonadjacent maximum sum");
    check(values==before,"input mutated");
}
int main() {
    verify({4,9,5,8},17); verify({},0); verify({0},0); verify({13},13);
    verify({8,1,1,8},16); verify({0,0,0},0); verify({8,9},9);
    unsigned count=1;
    const int alphabet[]{0,1,3};
    for (unsigned length=0; length<=7; ++length) {
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::vector<int> values;
            for (unsigned i=0; i<length; ++i) { values.push_back(alphabet[value%3]); value/=3; }
            verify(values,oracle(values));
        }
        count*=3;
    }
    verify(std::vector<int>(100,400),20000);
    verify(std::vector<int>(99,400),20000);
    std::cout << "House robber: passed\n";
}
