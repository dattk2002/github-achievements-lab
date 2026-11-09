#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

int oracle(const std::vector<int>& a) {
    int best = 0;
    for (std::size_t i = 0; i < a.size(); ++i)
        for (std::size_t j = i + 1; j < a.size(); ++j) {
            int h = a[i] < a[j] ? a[i] : a[j];
            int area = static_cast<int>(j - i) * h;
            if (area > best) best = area;
        }
    return best;
}
void check(std::vector<int> a, int expected) {
    auto original = a;
    require(lab::Solution{}.maxArea(a) == expected, "container result differs");
    require(a == original, "height input changed");
}
void enumerate(std::vector<int>& a, int remaining) {
    if (remaining == 0) { check(a, oracle(a)); return; }
    for (int h : {0, 1, 3, 5}) {
        a.push_back(h); enumerate(a, remaining - 1); a.pop_back();
    }
}
int main() {
    check({3, 8, 2, 7, 4, 8}, 32);
    check({2, 9, 1, 9, 2}, 18);
    check({5, 1, 1, 1, 5}, 20);
    check({0, 0}, 0); check({7}, 0); check({}, 0);
    std::vector<int> a;
    for (int n = 0; n <= 6; ++n) enumerate(a, n);
    check(std::vector<int>(100000, 10000), 999990000);
    check(std::vector<int>(100000, 0), 0);
    std::cout << "LC11: fixed, 5461 oracle and limit cases passed\n";
}
