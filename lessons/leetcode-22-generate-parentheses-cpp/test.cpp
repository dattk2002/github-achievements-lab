#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
// Generate all 2^(2n) bitstrings, then filter by the definition of balance.
std::set<std::string> oracle(int n) {
    std::set<std::string> result;
    for (unsigned mask = 0; mask < (1u << (2 * n)); ++mask) {
        int balance = 0; bool valid = true; std::string text;
        for (int i = 0; i < 2 * n; ++i) {
            const char symbol = (mask & (1u << i)) ? '(' : ')';
            text += symbol; balance += symbol == '(' ? 1 : -1;
            if (balance < 0) valid = false;
        }
        if (valid && balance == 0) result.insert(text);
    }
    return result;
}
int main() {
    const std::size_t catalan[]{0,1,2,5,14,42,132,429,1430};
    lab::Solution reused;
    for (int n = 1; n <= 8; ++n) {
        const auto output = reused.generateParenthesis(n);
        const std::set<std::string> actual(output.begin(), output.end());
        require(actual == oracle(n), "balanced combinations incomplete or invalid");
        require(actual.size() == output.size(), "duplicate combination");
        require(output.size() == catalan[n], "Catalan count differs");
    }
    require(reused.generateParenthesis(1) == std::vector<std::string>{"()"}, "state leaked");
    std::cout << "LC22: all n=1..8 against exhaustive bitstring oracle passed\n";
}
