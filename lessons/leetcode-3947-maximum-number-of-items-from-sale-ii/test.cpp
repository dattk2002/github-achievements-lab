#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
// Enumerate all affordable purchase-count vectors; no greedy/sieve in oracle.
int oracle(const std::vector<std::vector<int>>& items, int budget) {
    const int n = static_cast<int>(items.size());
    std::vector<int> gifts(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && items[j][0] % items[i][0] == 0) ++gifts[i];
    std::function<int(int,int)> visit = [&](int i, int money) {
        if (i == n) return 0;
        int best = 0;
        for (int copies = 0; copies <= money / items[i][1]; ++copies)
            best = std::max(best, copies + std::min(copies, gifts[i]) +
                            visit(i + 1, money - copies * items[i][1]));
        return best;
    };
    return visit(0, budget);
}
void check(std::vector<std::vector<int>> items, int budget, int expected) {
    const auto before = items;
    require(lab::Solution{}.maximumSaleItems(items, budget) == expected,
            "maximum copies differs from independent purchase enumeration");
    require(items == before, "items changed");
}
int main() {
    check({{1,4},{2,3},{3,8}}, 12, 5);
    check({{1,7}}, 20, 2);  // No self-gift, even with repeated purchases.
    check({{1,7}}, 6, 0);
    check({{2,4},{2,5},{1,9}}, 13, 5);  // Equal factors, distinct indices.
    check({{1,9},{2,4},{3,20}}, 12, 3); // Pair costs more than two singles.
    check({{1,8},{2,4},{3,20}}, 12, 3); // Equality at twice cheapest price.
    check({{1,4},{2,2},{3,20}}, 20, 10); // Limited gifts then singles.
    check({{1,10},{2,10},{3,10}}, 10, 2); // Free copies cannot generate gifts.
    unsigned checked = 0;
    for (int n = 1; n <= 3; ++n) {
        unsigned configurations = 1;
        const unsigned base = static_cast<unsigned>(4 * n);
        for (int i = 0; i < n; ++i) configurations *= base;
        for (unsigned code = 0; code < configurations; ++code) {
            auto digits = code;
            std::vector<std::vector<int>> items(n, std::vector<int>(2));
            for (auto& item : items) {
                const auto value = digits % base; digits /= base;
                item = {1 + static_cast<int>(value / 4), 1 + static_cast<int>(value % 4)};
            }
            for (int budget = 1; budget <= 12; ++budget) {
                check(items, budget, oracle(items, budget)); ++checked;
            }
        }
    }
    std::mt19937 random(3947);
    for (int trial = 0; trial < 500; ++trial) {
        const int n = 1 + static_cast<int>(random() % 7);
        std::vector<std::vector<int>> items(n, std::vector<int>(2));
        for (auto& item : items)
            item = {1 + static_cast<int>(random() % n), 1 + static_cast<int>(random() % 12)};
        const int budget = 1 + static_cast<int>(random() % 20);
        check(items, budget, oracle(items, budget));
    }
    check(std::vector<std::vector<int>>(100000, {1,1}), 1000000000, 2000000000);
    check(std::vector<std::vector<int>>(100000, {100000,1000000000}), 1000000000, 2);
    std::vector<std::vector<int>> distinct;
    for (int factor = 1; factor <= 100000; ++factor) distinct.push_back({factor,1});
    check(distinct, 1, 2);
    std::cout << "LC3947: " << checked << " exhaustive budgets, 500 random and boundary cases passed\n";
}
