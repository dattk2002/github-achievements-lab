#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
void check(std::vector<int> values, int expected) {
    const auto original = values;
    require(lab::Solution{}.findDuplicate(values) == expected, "duplicate differs");
    require(values == original, "input changed");
}
int main() {
    check({2, 4, 1, 3, 4}, 4);
    check({1, 1}, 1);
    check({2, 2, 2}, 2);
    check({1, 4, 4, 2, 4}, 4);
    // Exhaust all arrays in [1,n]^(n+1), retaining exactly one repeated value.
    unsigned checked = 0;
    for (int n = 1; n <= 5; ++n) {
        unsigned combinations = 1;
        for (int i = 0; i <= n; ++i) combinations *= static_cast<unsigned>(n);
        for (unsigned code = 0; code < combinations; ++code) {
            std::vector<int> values(static_cast<std::size_t>(n + 1));
            std::vector<int> frequency(static_cast<std::size_t>(n + 1), 0);
            unsigned digits = code;
            for (int& value : values) {
                value = 1 + static_cast<int>(digits % static_cast<unsigned>(n));
                digits /= static_cast<unsigned>(n);
                ++frequency[value];
            }
            int duplicate = 0;
            int repeated = 0;
            for (int value = 1; value <= n; ++value) {
                if (frequency[value] > 1) { duplicate = value; ++repeated; }
            }
            if (repeated == 1) { check(values, duplicate); ++checked; }
        }
    }
    std::vector<int> chain(100001);
    std::iota(chain.begin(), chain.end(), 1);
    chain.back() = 100000;
    check(chain, 100000);
    chain.back() = 1;
    check(chain, 1);
    std::mt19937 random(287);
    std::shuffle(chain.begin(), chain.end(), random);
    check(chain, 1);
    check(std::vector<int>(100001, 100000), 100000);
    std::cout << "LC287: " << checked << " exhaustive, fixed and boundary cases passed\n";
}
