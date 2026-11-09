#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

int oracle(const std::vector<int>& a, std::size_t start = 0) {
    int best = 0;
    for (std::size_t buy = start; buy < a.size(); ++buy)
        for (std::size_t sell = buy + 1; sell < a.size(); ++sell) {
            int profit = a[sell] - a[buy] + oracle(a, sell + 2);
            if (profit > best) best = profit;
        }
    return best;
}
void check(std::vector<int> a, int expected) {
    auto original = a;
    require(lab::Solution{}.maxProfit(a) == expected, "cooldown result differs");
    require(a == original, "price input changed");
}
void enumerate(std::vector<int>& a, int remaining) {
    if (remaining == 0) { check(a, oracle(a)); return; }
    for (int p : {0,1,3}) {
        a.push_back(p); enumerate(a, remaining - 1); a.pop_back();
    }
}
int main() {
    check({2,5,1,2,6},7); check({1,4,2,7},6);
    check({1,2,3,0,2},3); check({9,7,5,2},0);
    check({},0); check({6},0); check({0,0},0);
    std::vector<int> a;
    for (int n = 0; n <= 7; ++n) enumerate(a,n);
    for (int i = 0; i < 1250; ++i) a.insert(a.end(),{0,1000,0,0});
    check(a,1250000); check(std::vector<int>(5000,1000),0);
    std::cout << "LC309: fixed, 3280 transaction-oracle and limit cases passed\n";
}
