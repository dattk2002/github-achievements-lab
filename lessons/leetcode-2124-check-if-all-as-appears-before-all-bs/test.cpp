#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace lab {
namespace {
void check(const std::string& input, bool expected) {
    Solution solution;
    const bool actual = solution.checkString(input);
    if (actual != expected) {
        std::cerr << std::boolalpha << "checkString(\"" << input
                  << "\"): expected " << expected << ", got " << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}  // namespace

void run_tests() {
    check("ba", false);
    check("ab", true);
    check("a", true);
    check("b", true);
    check("aaaa", true);
    check("bbbbb", true);
    check("aabbbb", true);
    check("abbaab", false);
    check(std::string(99, 'a') + 'b', true);
    check(std::string(99, 'b') + 'a', false);
    check('b' + std::string(99, 'a'), false);
    std::cout << "checkString: 11 cases passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
