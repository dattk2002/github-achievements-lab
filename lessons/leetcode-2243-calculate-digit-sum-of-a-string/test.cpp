#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace lab {
namespace {
void check(const std::string& input, int k, const std::string& expected) {
    const std::string actual = Solution{}.digitSum(input, k);
    if (actual != expected) {
        std::cerr << "digitSum(" << input << ", " << k << "): expected "
                  << expected << ", got " << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}  // namespace

void run_tests() {
    check("12345", 3, "69");       // Partial final group: 123 | 45.
    check("9876", 3, "246");       // Keep 24 as two digits, then append 6.
    check("99999", 2, "99");       // 18189 -> 999 -> 189 -> 99.
    check("00000", 2, "00");      // 000 -> 00; zero is not an empty group.
    check("001234", 3, "19");     // 001 | 234; leading zeros are digits.
    check("0001", 2, "01");       // Preserve zero-valued groups in output.
    check("123456", 3, "615");    // Stop at length k, even with a two-digit sum.
    check("7", 2, "7");
    check("09", 2, "09");         // Equality must stop without summing.
    check("00042", 100, "00042"); // No round; preserve initial representation.
    check(std::string(100, '9'), 100, std::string(100, '9'));
    check(std::string(100, '9'), 99, "8919"); // First 99 nines sum to 891; last digit is 9.
    check(std::string(100, '0'), 2, "00");
    check(std::string(100, '9'), 2, "99");
    std::cout << "digit sum: 14 cases passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
