#include "lesson.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

// Enumerate every possible set of cuts, then reject cross-part character reuse.
std::vector<int> oracle(const std::string& text) {
    if (text.empty()) return {};
    std::vector<int> best;
    for (unsigned cuts = 0; cuts < (1U << (text.size() - 1)); ++cuts) {
        std::array<int, 26> owner;
        owner.fill(-1);
        int part = 0, length = 0;
        bool valid = true;
        std::vector<int> sizes;
        for (std::size_t i = 0; i < text.size(); ++i) {
            const auto letter = static_cast<std::size_t>(text[i] - 'a');
            if (owner[letter] != -1 && owner[letter] != part) { valid = false; break; }
            owner[letter] = part;
            ++length;
            if (i + 1 == text.size() || (cuts & (1U << i)) != 0) {
                sizes.push_back(length);
                length = 0;
                ++part;
            }
        }
        if (valid && sizes.size() > best.size()) best = sizes;
    }
    return best;
}

void check(const std::string& text, const std::vector<int>& expected) {
    const auto original = text;
    require(lab::Solution{}.partitionLabels(text) == expected, "LC763: maximal partition differs");
    require(text == original, "LC763: input changed");
}

int main() {
    check("abacddce", {3, 4, 1});
    check("abcd", {1, 1, 1, 1});
    check("abca", {4});
    check("a", {1});
    check("", {});
    std::size_t cases = 0;
    for (int length = 0; length <= 7; ++length) {
        unsigned possibilities = 1;
        for (int i = 0; i < length; ++i) possibilities *= 3;
        for (unsigned code = 0; code < possibilities; ++code) {
            auto rest = code;
            std::string text(length, 'a');
            for (char& letter : text) { letter = static_cast<char>('a' + rest % 3); rest /= 3; }
            check(text, oracle(text));
            ++cases;
        }
    }
    check(std::string(500, 'z'), {500});
    std::string cyclic;
    for (int i = 0; i < 500; ++i) cyclic += static_cast<char>('a' + i % 3);
    check(cyclic, {500});
    check("abcdefghijklmnopqrstuvwxyz", std::vector<int>(26, 1));
    for (const auto& bad : std::vector<std::string>{"aA", "{", std::string(1, static_cast<char>(0xff)), std::string("a\0b", 3)}) {
        bool threw = false;
        try { (void)lab::Solution{}.partitionLabels(bad); }
        catch (const std::invalid_argument&) { threw = true; }
        require(threw, "LC763: non-lowercase byte must throw");
    }
    std::cout << "LC763: fixed, " << cases << " cut-enumeration oracle, invalid and limit cases passed\n";
}
