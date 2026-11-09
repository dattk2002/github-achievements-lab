#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

int oracle(const std::string& a, const std::string& b) {
    int best = 0;
    for (unsigned mask = 0; mask < (1U << a.size()); ++mask) {
        std::size_t cursor = 0;
        int length = 0;
        bool found = true;
        for (std::size_t i = 0; i < a.size(); ++i) {
            if ((mask & (1U << i)) == 0) continue;
            while (cursor < b.size() && b[cursor] != a[i]) ++cursor;
            if (cursor == b.size()) { found = false; break; }
            ++cursor; ++length;
        }
        if (found && length > best) best = length;
    }
    return best;
}
void check(const std::string& a, const std::string& b, int expected) {
    require(lab::Solution{}.longestCommonSubsequence(a,b) == expected, "LCS result differs");
}
int main() {
    check("axbycz", "abc", 3); check("stone", "tones", 4);
    check("aaaa", "aa", 2); check("abc", "def", 0);
    check("", "", 0); check("abc", "", 0); check("", "abc", 0);
    std::vector<std::string> words;
    for (int n = 0; n <= 5; ++n)
        for (unsigned mask = 0; mask < (1U << n); ++mask) {
            std::string word;
            for (int i = 0; i < n; ++i) word += ((mask & (1U << i)) != 0) ? 'a' : 'b';
            words.push_back(word);
        }
    for (const auto& a : words) for (const auto& b : words) check(a,b,oracle(a,b));
    check(std::string(1000,'a'),std::string(1000,'a'),1000);
    check(std::string(1000,'a'),std::string(1000,'b'),0);
    std::string a,b;
    for (int i = 0; i < 500; ++i) { a += "ab"; b += "ba"; }
    check(a,b,999);
    std::cout << "LC1143: fixed, 3969 subsequence-oracle and limit cases passed\n";
}
