#include "lesson.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Explore every legal forward edge, rather than tracking a greedy frontier.
bool oracle(const std::vector<int>& jumps) {
    if (jumps.empty()) return false;
    std::vector<bool> reachable(jumps.size(), false);
    reachable[0] = true;
    for (std::size_t i = 0; i < jumps.size(); ++i) {
        if (!reachable[i]) continue;
        for (std::size_t j = i + 1; j < jumps.size(); ++j)
            if (j - i <= static_cast<std::size_t>(jumps[i])) reachable[j] = true;
    }
    return reachable.back();
}

void check(std::vector<int> jumps, bool expected) {
    const auto original = jumps;
    require(lab::Solution{}.canJump(jumps) == expected, "LC55: reachability differs");
    require(jumps == original, "LC55: input changed");
}

int main() {
    check({2, 0, 2, 0, 0}, true);
    check({1, 0, 2}, false);
    check({0}, true);
    check({0, 1}, false);
    check({2, 0, 0}, true);
    check({1, INT_MAX, 0, 0}, true);
    check({}, false);
    std::size_t cases = 0;
    for (int length = 0; length <= 8; ++length) {
        unsigned possibilities = 1;
        for (int i = 0; i < length; ++i) possibilities *= 4;
        for (unsigned code = 0; code < possibilities; ++code) {
            auto rest = code;
            std::vector<int> jumps(length);
            for (int& jump : jumps) { jump = static_cast<int>(rest % 4); rest /= 4; }
            check(jumps, oracle(jumps));
            ++cases;
        }
    }
    check(std::vector<int>(10000, 1), true);
    std::vector<int> blocked(10000, 1);
    blocked[9998] = 0;
    check(blocked, false);
    check(std::vector<int>(10000, 100000), true);
    for (auto bad : std::vector<std::vector<int>>{{-1}, {0, -1}, {10, 0, -1}}) {
        const auto original = bad;
        bool threw = false;
        try { (void)lab::Solution{}.canJump(bad); }
        catch (const std::invalid_argument&) { threw = true; }
        require(threw && bad == original, "LC55: negative jump must throw without mutation");
    }
    std::cout << "LC55: fixed, " << cases << " reachability-oracle, invalid and limit cases passed\n";
}
