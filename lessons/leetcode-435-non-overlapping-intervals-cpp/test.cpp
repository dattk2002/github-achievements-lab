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
#include <functional>
using Intervals = std::vector<std::vector<int>>;
int oracle(const Intervals& a) {
    int best = 0;
    const unsigned limit = 1U << a.size();
    for (unsigned mask = 0; mask < limit; ++mask) {
        Intervals selected;
        for (std::size_t i = 0; i < a.size(); ++i)
            if ((mask & (1U << i)) != 0) selected.push_back(a[i]);
        std::sort(selected.begin(), selected.end());
        bool valid = true;
        for (std::size_t i = 1; i < selected.size(); ++i)
            if (selected[i-1][1] > selected[i][0]) valid = false;
        if (valid && static_cast<int>(selected.size()) > best)
            best = static_cast<int>(selected.size());
    }
    return static_cast<int>(a.size()) - best;
}
void check(Intervals a, int expected) {
    auto original = a;
    require(lab::Solution{}.eraseOverlapIntervals(a) == expected, "interval result differs");
    require(a == original, "interval input changed");
}
void enumerate(Intervals& a, int remaining) {
    if (remaining == 0) { check(a, oracle(a)); return; }
    for (const auto& interval : Intervals{{-2,-1},{-1,0},{0,1},{-2,0},{-1,1},{-2,1}}) {
        a.push_back(interval); enumerate(a, remaining-1); a.pop_back();
    }
}
void invalid(Intervals a) {
    const auto original = a;
    bool threw = false;
    try { (void)lab::Solution{}.eraseOverlapIntervals(a); }
    catch (const std::invalid_argument&) { threw = true; }
    require(threw, "malformed interval must throw invalid_argument");
    require(a == original, "invalid input changed");
}
int main() {
    check({{0,10},{1,2},{2,3},{3,4}}, 1);
    check({{1,2},{1,2},{2,3}}, 1);
    check({{4,7},{1,4},{7,8}}, 0);
    check({{1,10},{2,9},{3,8}}, 2); check({}, 0);
    Intervals a;
    for (int n = 0; n <= 5; ++n) enumerate(a, n);
    invalid({{0}}); invalid({{0,1,2}}); invalid({{2,2}});
    invalid({{2,1}}); invalid({{0,1},{}});
    check(Intervals(100000, std::vector<int>{0,1}), 99999);
    Intervals chain;
    for (int i = 0; i < 100000; ++i) chain.push_back({-50000+i,-49999+i});
    check(chain, 0);
    std::cout << "LC435: fixed, 9331 subset-oracle, invalid and limit cases passed\n";
}
