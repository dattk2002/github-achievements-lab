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

void check(int m, int n, int expected) {
    require(lab::Solution{}.uniquePaths(m,n) == expected, "path count differs");
}
// Count step permutations by binomial coefficients, independently of grid DP.
long long choose(int n, int k) {
    k = std::min(k,n-k);
    long long value = 1;
    for (int i=1; i<=k; ++i) {
        value = value*(n-k+i)/i;
        if (value>2000000000LL) return value;
    }
    return value;
}
int main() {
    check(4,4,20); check(2,5,5); check(1,1,1);
    check(1,100,1); check(100,1,1); check(17,17,601080390);
    check(2,100,100); check(100,2,100);
    for (int m=1; m<=100; ++m) for (int n=1; n<=100; ++n) {
        const auto expected=choose(m+n-2,m-1);
        if (expected<=2000000000LL) check(m,n,static_cast<int>(expected));
        else throws<std::overflow_error>([&] { (void)lab::Solution{}.uniquePaths(m,n); });
    }
    for (const auto dims: std::vector<std::pair<int,int>>{{0,1},{1,0},{-1,4},{4,-1},{101,2},{2,101}})
        throws<std::invalid_argument>([&] { (void)lab::Solution{}.uniquePaths(dims.first,dims.second); });
    std::cout << "LC62: fixed, 10000 binomial-oracle and invalid-dimension cases passed\n";
}
