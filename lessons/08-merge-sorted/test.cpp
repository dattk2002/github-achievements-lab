#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <algorithm>
void verify(const std::vector<int>& a, const std::vector<int>& b) {
    const auto before_a=a, before_b=b;
    auto expected=a;
    expected.insert(expected.end(),b.begin(),b.end());
    std::sort(expected.begin(),expected.end());
    check(lab::merge_sorted(a,b)==expected, "merge values, order or multiplicity");
    check(a==before_a && b==before_b, "merge mutated input");
}
int main() {
    check(lab::merge_sorted({1,4,4},{-2,4,8})==std::vector<int>({-2,1,4,4,4,8}), "hand-checked merge");
    verify({},{}); verify({},{-2,0,3}); verify({-2,0,3},{});
    verify({1},{2,3,4,5,6}); verify({2,3,4,5,6},{1});
    verify({-8,-3,0},{-9,-3,0,5}); verify({4,4,4},{4,4});
    verify({std::numeric_limits<int>::min(),0},{-1,std::numeric_limits<int>::max()});
    const std::vector<int> same{-3,0,0,8}; verify(same,same);
    unsigned state=123;
    for (unsigned n=0; n<=24; ++n) for (unsigned m=0; m<=24; ++m) {
        std::vector<int> a,b;
        for (unsigned i=0; i<n+m; ++i) {
            state=state*1664525U+1013904223U;
            (i<n ? a : b).push_back(static_cast<int>(state%21)-10);
        }
        std::sort(a.begin(),a.end()); std::sort(b.begin(),b.end()); verify(a,b);
    }
    std::cout << "Merge: passed\n";
}
