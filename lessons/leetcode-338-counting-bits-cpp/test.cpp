#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

int oracle(int number) {
    int ones = 0;
    while (number != 0) { ones += number % 2; number /= 2; }
    return ones;
}

void check(int n) {
    const auto actual = lab::Solution{}.countBits(n);
    require(actual.size() == static_cast<std::size_t>(n) + 1, "LC338: wrong output length");
    for (int i = 0; i <= n; ++i)
        require(actual[i] == oracle(i), "LC338: wrong bit count");
}

int main() {
    require(lab::Solution{}.countBits(0) == std::vector<int>{0}, "LC338: zero has no set bits");
    require(lab::Solution{}.countBits(8) == std::vector<int>({0, 1, 1, 2, 1, 2, 2, 3, 1}),
            "LC338: fixed binary boundaries differ");
    for (int n = 0; n <= 256; ++n) check(n);
    check(100000);
    auto first = lab::Solution{}.countBits(3);
    first[0] = 99;
    require(lab::Solution{}.countBits(3)[0] == 0, "LC338: calls share mutable state");
    bool threw = false;
    try { (void)lab::Solution{}.countBits(-1); }
    catch (const std::invalid_argument&) { threw = true; }
    require(threw, "LC338: negative n must throw");
    std::cout << "LC338: fixed, division-oracle through 100000 and invalid cases passed\n";
}
