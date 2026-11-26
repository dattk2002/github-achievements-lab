#include "lesson.hpp"

#include <cstdlib>
#include <iostream>

namespace lab {
int run_tests() {
    Solution solution;
    bool passed = true;
    for (int n = 1; n <= 50; ++n) {
        // Hand-summed move costs give the intervals with 1, 3, 5, or 7 moves.
        const bool expected = (10 <= n && n <= 18) ||
                              (27 <= n && n <= 33) ||
                              (40 <= n && n <= 44) ||
                              (49 <= n && n <= 50);
        const bool actual = solution.canAliceWin(n);
        if (actual != expected) {
            std::cerr << "n=" << n << ": expected " << std::boolalpha
                      << expected << ", got " << actual << '\n';
            passed = false;
        }
    }
    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
}  // namespace lab

int main() { return lab::run_tests(); }
