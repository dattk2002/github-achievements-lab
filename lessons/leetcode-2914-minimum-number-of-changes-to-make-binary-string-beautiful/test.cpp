#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace lab {
namespace {
void check(const std::string& input, int expected) {
    const int actual = Solution{}.minChanges(input);
    if (actual != expected) {
        std::cerr << "Input length " << input.size()
                  << ", prefix " << input.substr(0, 24)
                  << ": expected " << expected << ", got " << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}

bool has_even_runs(const std::string& candidate) {
    std::size_t start = 0;
    while (start < candidate.size()) {
        std::size_t end = start + 1;
        while (end < candidate.size() && candidate[end] == candidate[start]) {
            ++end;
        }
        if ((end - start) % 2 != 0) {
            return false;
        }
        start = end;
    }
    return true;
}

void check_all_short_inputs() {
    for (int length = 2; length <= 8; length += 2) {
        std::vector<std::string> inputs;
        std::vector<std::string> beautiful;
        for (int mask = 0; mask < (1 << length); ++mask) {
            std::string candidate(length, '0');
            for (int i = 0; i < length; ++i) {
                if ((mask & (1 << i)) != 0) {
                    candidate[i] = '1';
                }
            }
            inputs.push_back(candidate);
            if (has_even_runs(candidate)) {
                beautiful.push_back(candidate);
            }
        }

        for (const auto& input : inputs) {
            int expected = length;
            for (const auto& target : beautiful) {
                int edits = 0;
                for (int i = 0; i < length; ++i) {
                    if (input[i] != target[i]) {
                        ++edits;
                    }
                }
                expected = std::min(expected, edits);
            }
            check(input, expected);
        }
    }
}
}  // namespace

void run_tests() {
    check("11", 0);
    check("01", 1);
    check("00111100", 0);
    check("000111", 1);
    check("110001", 1);
    check("010101", 3);
    check(std::string(100000, '1'), 0);

    std::string alternating(100000, '0');
    for (std::size_t i = 1; i < alternating.size(); i += 2) {
        alternating[i] = '1';
    }
    check(alternating, 50000);
    check_all_short_inputs();
    std::cout << "LeetCode 2914: boundary cases and 340 exhaustive inputs passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
