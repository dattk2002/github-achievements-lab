#include "lesson.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Enumerate the sign of every position; equal values and signed zeros stay distinct.
std::map<int, int> oracle(const std::vector<int>& nums) {
    std::map<int, int> counts;
    for (unsigned mask = 0; mask < (1U << nums.size()); ++mask) {
        int sum = 0;
        for (std::size_t i = 0; i < nums.size(); ++i)
            sum += ((mask & (1U << i)) != 0) ? nums[i] : -nums[i];
        ++counts[sum];
    }
    return counts;
}

void check(std::vector<int> nums, int target, int expected) {
    const auto original = nums;
    require(lab::Solution{}.findTargetSumWays(nums, target) == expected, "LC494: expression count differs");
    require(nums == original, "LC494: input changed");
}

void invalid(std::vector<int> nums) {
    const auto original = nums;
    bool threw = false;
    try { (void)lab::Solution{}.findTargetSumWays(nums, INT_MAX); }
    catch (const std::invalid_argument&) { threw = true; }
    require(threw && nums == original, "LC494: invalid input must throw before target shortcut");
}

int main() {
    check({0, 0, 1}, 1, 4);
    check({1, 2, 3}, 0, 2);
    check({2, 2}, 0, 2);
    check({2, 4}, 1, 0);
    check({2, 4}, -6, 1);
    check({}, 0, 1);
    check({}, 1, 0);
    check({1, 2}, INT_MIN, 0);
    check({1, 2}, INT_MAX, 0);
    std::size_t cases = 0;
    for (int length = 0; length <= 6; ++length) {
        unsigned possibilities = 1;
        for (int i = 0; i < length; ++i) possibilities *= 3;
        for (unsigned code = 0; code < possibilities; ++code) {
            auto rest = code;
            std::vector<int> nums(length);
            int total = 0;
            for (int& value : nums) { value = static_cast<int>(rest % 3); rest /= 3; total += value; }
            auto counts = oracle(nums);
            for (int target = -total - 1; target <= total + 1; ++target) {
                check(nums, target, counts[target]);
                ++cases;
            }
        }
    }
    check(std::vector<int>(20, 0), 0, 1048576);
    check(std::vector<int>(20, 1), 0, 184756);
    check(std::vector<int>(20, 50), 1000, 1);
    check({1000}, -1000, 1);
    invalid({-1, 2});
    invalid({1000, 1});
    invalid(std::vector<int>(21, 0));
    std::cout << "LC494: fixed, " << cases << " sign-enumeration oracle, zero, invalid and limit cases passed\n";
}
