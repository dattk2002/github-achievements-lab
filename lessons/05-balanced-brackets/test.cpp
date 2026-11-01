#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

void expect(std::string_view text, bool wanted) {
    if (lab::balanced_brackets(text) != wanted) {
        std::cerr << "balanced brackets: unexpected validity for length " << text.size() << '\n';
        std::exit(EXIT_FAILURE);
    }
}

bool reduction_oracle(std::string_view text) {
    std::string brackets;
    for (char ch : text) if (std::string_view("()[]{}").find(ch) != std::string_view::npos)
        brackets.push_back(ch);
    bool changed = true;
    while (changed) {
        changed = false;
        for (std::string_view pair : {"()", "[]", "{}"}) {
            const auto position = brackets.find(pair);
            if (position != std::string::npos) {
                brackets.erase(position, 2);
                changed = true;
            }
        }
    }
    return brackets.empty();
}

int main() {
    expect("", true);
    expect("abc 123", true);
    expect("()[]{}", true);
    expect("a{b[c(d)e]f}g", true);
    expect(")", false);
    expect("(", false);
    expect("([)]", false);
    expect("{]", false);
    expect("())(", false);
    expect("[{}]}", false);
    expect("(([])", false);
    expect(std::string_view("(\0)", 3), true);
    expect(std::string_view("(\0]", 3), false);
    expect(std::string_view("(\0", 2), false);
    expect(std::string(20000, '(') + std::string(20000, ')'), true);
    expect(std::string(20000, '('), false);
    constexpr std::string_view alphabet = "()[]{}x";
    // Repeated pair deletion is independent of the implementation's stack.
    for (int length = 0, combinations = 1; length <= 6; ++length, combinations *= 7) {
        for (int code = 0; code < combinations; ++code) {
            std::string text;
            int digits = code;
            for (int i = 0; i < length; ++i, digits /= 7) text.push_back(alphabet[digits % 7]);
            expect(text, reduction_oracle(text));
        }
    }
    std::cout << "balanced brackets: all cases passed\n";
}
