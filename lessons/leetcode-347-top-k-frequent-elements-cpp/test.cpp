#include "lesson.hpp"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Validate the selected set by comparing every selected/unselected frequency.
// This accepts any legal selection at a tied cutoff, without assuming order.
void check(std::vector<int> nums, int k) {
    const auto original = nums;
    const auto result = lab::Solution{}.topKFrequent(nums, k);
    require(nums == original, "LC347: input changed");
    require(result.size() == static_cast<std::size_t>(k), "LC347: wrong number of results");
    const std::set<int> selected(result.begin(), result.end());
    require(selected.size() == result.size(), "LC347: duplicate result");
    std::map<int, int> counts;
    for (int value : nums) ++counts[value];
    for (int value : result) {
        require(counts.count(value) == 1, "LC347: invented value");
        for (const auto& entry : counts)
            if (selected.count(entry.first) == 0)
                require(counts.at(value) >= entry.second, "LC347: omitted a more frequent value");
    }
}

void invalid(std::vector<int> nums, int k) {
    const auto original = nums;
    bool threw = false;
    try { (void)lab::Solution{}.topKFrequent(nums, k); }
    catch (const std::invalid_argument&) { threw = true; }
    require(threw && nums == original, "LC347: invalid k must throw without mutation");
}

int main() {
    std::vector<int> fixed{8, -2, 8, 5, -2, 8, 5, 8};
    auto result = lab::Solution{}.topKFrequent(fixed, 1);
    require(result == std::vector<int>{8}, "LC347: fixed winner differs");
    check(fixed, 2);
    check({INT_MIN, INT_MAX, INT_MIN, 0}, 1);
    check({4, 4, 4}, 1);
    check({-1, 0, 1}, 3);
    check({-1, 0, 1}, 1);
    check({}, 0);
    check({1}, 0);
    std::size_t cases = 0;
    for (int length = 0; length <= 7; ++length) {
        unsigned possibilities = 1;
        for (int i = 0; i < length; ++i) possibilities *= 3;
        for (unsigned code = 0; code < possibilities; ++code) {
            auto rest = code;
            std::vector<int> nums(length);
            for (int& value : nums) { value = static_cast<int>(rest % 3) - 1; rest /= 3; }
            const std::set<int> unique(nums.begin(), nums.end());
            for (int k = 0; k <= static_cast<int>(unique.size()); ++k) {
                check(nums, k);
                ++cases;
            }
        }
    }
    std::vector<int> large(100000, 9);
    large[0] = -10000;
    large[1] = 10000;
    check(large, 1);
    large.clear();
    for (int value = -10000; value <= 10000; ++value) large.push_back(value);
    check(large, 100);
    invalid({}, 1);
    invalid({1, 1}, 2);
    invalid({1, 2}, -1);
    std::cout << "LC347: fixed, " << cases << " frequency-oracle, ties, invalid and limit cases passed\n";
}
