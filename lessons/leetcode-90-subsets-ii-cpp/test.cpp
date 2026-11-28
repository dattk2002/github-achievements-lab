#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
std::set<std::vector<int>> oracle(const std::vector<int>& values) {
    std::set<std::vector<int>> result;
    for (unsigned mask = 0; mask < (1u << values.size()); ++mask) {
        std::vector<int> subset;
        for (std::size_t i = 0; i < values.size(); ++i)
            if (mask & (1u << i)) subset.push_back(values[i]);
        std::sort(subset.begin(), subset.end()); result.insert(subset);
    }
    return result;
}
void check(std::vector<int> values) {
    const auto before = values;
    auto output = lab::Solution{}.subsetsWithDup(values);
    for (auto& subset : output) std::sort(subset.begin(), subset.end());
    const std::set<std::vector<int>> actual(output.begin(), output.end());
    require(actual == oracle(before), "missing or unexpected subset");
    require(actual.size() == output.size(), "duplicate subset returned");
    require(values == before, "input changed");
}
int main() {
    check({3,1,3}); check({-10,10,-10}); check({0});
    unsigned checked = 0;
    unsigned configurations = 3;
    for (int n = 1; n <= 7; ++n) {
        for (unsigned code = 0; code < configurations; ++code) {
            unsigned digits = code;
            std::vector<int> values(n);
            for (int& value : values) { value = static_cast<int>(digits % 3) - 1; digits /= 3; }
            check(values); ++checked;
        }
        configurations *= 3;
    }
    check(std::vector<int>(10, 4));
    std::vector<int> unique(10); std::iota(unique.begin(), unique.end(), -5); check(unique);
    std::vector<int> a{2,2}, b{7}; lab::Solution reused;
    require(reused.subsetsWithDup(a).size() == 3 && reused.subsetsWithDup(b).size() == 2,
            "state leaked across calls");
    std::cout << "LC90: " << checked << " exhaustive arrays and boundaries passed\n";
}
