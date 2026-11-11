#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace lab {
namespace {
void check(int c1, int c2, int cb, int n1, int n2, long long expected) {
    const long long actual = Solution{}.minimumCost(c1, c2, cb, n1, n2);
    if (actual != expected) {
        std::cerr << "costs=" << c1 << ',' << c2 << ',' << cb
                  << " needs=" << n1 << ',' << n2 << ": expected "
                  << expected << ", got " << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}

// Enumerate actual purchase counts, independently of the breakpoint solution.
long long exhaustive(int c1, int c2, int cb, int n1, int n2) {
    long long best = std::numeric_limits<long long>::max();
    for (int a = 0; a <= n1; ++a) {
        for (int b = 0; b <= n2; ++b) {
            for (int both = 0; both <= std::max(n1, n2); ++both) {
                if (a + both >= n1 && b + both >= n2) {
                    best = std::min(best, 1LL * a * c1 + 1LL * b * c2
                                          + 1LL * both * cb);
                }
            }
        }
    }
    return best;
}
}  // namespace

void run_tests() {
    check(7, 4, 8, 0, 0, 0);
    check(7, 4, 8, 4, 2, 30);  // Two pairs plus two type-1 items.
    check(4, 7, 8, 2, 4, 30);  // Exchange the two requirements.
    check(9, 6, 2, 4, 1, 8);   // Buying beyond the smaller need is optimal.
    check(6, 9, 2, 1, 4, 8);
    check(2, 3, 9, 4, 5, 23);  // No shared items.
    check(7, 4, 8, 3, 3, 24);  // Equal needs.
    check(2, 3, 5, 4, 2, 14);  // Shared price equals separate prices.
    check(5, 2, 5, 4, 2, 20);  // Flat cost after the smaller need.
    check(8, 3, 2, 0, 5, 10);  // Zero need still allows cheap shared items.
    check(3, 8, 2, 5, 0, 10);
    check(8, 3, 9, 0, 5, 15);
    check(3, 8, 9, 5, 0, 15);
    check(1, 1, 1, 1, 1, 1);
    check(1000000, 1000000, 1000000, 1000000000, 1000000000,
          1000000000000000LL);
    check(999999, 999999, 1000000, 1000000000, 0,
          999999000000000LL);
    check(1000000, 1000000, 1, 1000000000, 999999999, 1000000000LL);
    check(1000000, 1, 1000000, 1000000000, 1, 1000000000000000LL);

    int cases = 0;
    for (int c1 = 1; c1 <= 6; ++c1)
        for (int c2 = 1; c2 <= 6; ++c2)
            for (int cb = 1; cb <= 6; ++cb)
                for (int n1 = 0; n1 <= 5; ++n1)
                    for (int n2 = 0; n2 <= 5; ++n2) {
                        check(c1, c2, cb, n1, n2,
                              exhaustive(c1, c2, cb, n1, n2));
                        ++cases;
                    }
    std::cout << "minimum cost: boundary cases and " << cases
              << " exhaustive inputs passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
