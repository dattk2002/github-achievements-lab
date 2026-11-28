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
void check(std::vector<int> values) {
    const auto before = values;
    const int expected = *std::min_element(values.begin(), values.end());
    require(lab::Solution{}.findMin(values) == expected, "minimum differs from linear oracle");
    require(values == before, "input changed");
}
int main() {
    check({9,12,-4,0,3}); check({7}); check({-3,2}); check({2,-3});
    unsigned checked = 0;
    for (int n = 1; n <= 150; ++n) {
        std::vector<int> values(n);
        for (int i = 0; i < n; ++i) values[i] = -500 + 3 * i;
        for (int shift = 0; shift < n; ++shift) {
            check(values); ++checked;
            std::rotate(values.begin(), values.begin() + 1, values.end());
        }
    }
    std::mt19937 random(153);
    for (int trial = 0; trial < 500; ++trial) {
        std::vector<int> pool(10001); std::iota(pool.begin(), pool.end(), -5000);
        std::shuffle(pool.begin(), pool.end(), random);
        pool.resize(1 + random() % 200); std::sort(pool.begin(), pool.end());
        std::rotate(pool.begin(), pool.begin() + random() % pool.size(), pool.end()); check(pool);
    }
    std::vector<int> large(5000); std::iota(large.begin(), large.end(), -2500);
    for (int shift : {0,1,2499,4998,4999}) {
        auto rotated = large;
        std::rotate(rotated.begin(), rotated.begin() + shift, rotated.end()); check(rotated);
    }
    std::cout << "LC153: " << checked << " complete rotations, 500 random and boundaries passed\n";
}
