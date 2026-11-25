#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
// Try all three substitutions of every star; prune invalid prefixes.
bool oracle(const std::string& text, std::size_t position = 0, int open = 0) {
    if (open < 0) return false;
    if (position == text.size()) return open == 0;
    const char ch = text[position];
    if (ch == '(') return oracle(text, position + 1, open + 1);
    if (ch == ')') return oracle(text, position + 1, open - 1);
    return oracle(text, position + 1, open) ||
           oracle(text, position + 1, open + 1) ||
           oracle(text, position + 1, open - 1);
}
void check(const std::string& text, bool expected) {
    require(lab::Solution{}.checkValidString(text) == expected, "wildcard validity mismatch");
}
int main() {
    check("(*()*)", true);
    check(")*", false);
    check("*(", false);
    check("", true);
    check("*", true);
    check("(", false);
    check("((**", true);
    unsigned count = 1;
    for (int length = 0; length <= 9; ++length) {
        for (unsigned encoded = 0; encoded < count; ++encoded) {
            unsigned digits = encoded;
            std::string text(static_cast<std::size_t>(length), '(');
            for (char& ch : text) { ch = "()*"[digits % 3]; digits /= 3; }
            check(text, oracle(text));
        }
        count *= 3;
    }
    check(std::string(100, '*'), true);
    check(std::string(50, '(') + std::string(50, '*'), true);
    check(std::string(51, '(') + std::string(49, '*'), false);
    check(std::string(100, ')'), false);
    std::cout << "LC678: fixed, 29524 exhaustive and length-100 cases passed\n";
}
