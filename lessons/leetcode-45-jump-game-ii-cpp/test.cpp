#include "lesson.hpp"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Relax every legal forward edge, independently of the greedy layer boundary.
int oracle(const std::vector<int>& nums) {
    if (nums.empty()) return -1;
    std::vector<int> distance(nums.size(), -1);
    distance[0] = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (distance[i] < 0) continue;
        for (std::size_t j = i + 1; j < nums.size(); ++j) {
            if (j - i > static_cast<std::size_t>(nums[i])) continue;
            const int candidate = distance[i] + 1;
            if (distance[j] < 0 || candidate < distance[j]) distance[j] = candidate;
        }
    }
    return distance.back();
}

void check(std::vector<int> nums, int expected) {
    const auto original = nums;
    require(lab::Solution{}.jump(nums) == expected, "LC45: minimum jump count differs");
    require(nums == original, "LC45: input changed");
}

int main() {
    check({2, 0, 3, 0, 0, 1}, 2);
    check({1, 2, 1, 1, 0}, 3);
    check({0}, 0);
    check({0, 1}, -1);
    check({1, 0, 1}, -1);
    check({2, 0, 0}, 1);
    check({1, INT_MAX, 0, 0}, 2);
    check({}, -1);
    std::size_t cases = 0;
    for (int length = 0; length <= 8; ++length) {
        unsigned possibilities = 1;
        for (int i = 0; i < length; ++i) possibilities *= 4;
        for (unsigned code = 0; code < possibilities; ++code) {
            auto rest = code;
            std::vector<int> nums(length);
            for (int& value : nums) { value = static_cast<int>(rest % 4); rest /= 4; }
            check(nums, oracle(nums));
            ++cases;
        }
    }
    check(std::vector<int>(10000, 1), 9999);
    check(std::vector<int>(10000, 1000), 10);
    std::vector<int> blocked(10000, 1);
    blocked[9998] = 0;
    check(blocked, -1);
    for (auto bad : std::vector<std::vector<int>>{{-1}, {0, -1}, {10, 0, -1}}) {
        const auto original = bad;
        bool threw = false;
        try { (void)lab::Solution{}.jump(bad); }
        catch (const std::invalid_argument&) { threw = true; }
        require(threw && bad == original, "LC45: negative jump must throw without mutation");
    }
    std::cout << "LC45: fixed, " << cases << " edge-relaxation oracle, invalid and limit cases passed\n";
}
