#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

namespace lab {
class Solution {
public:
    int numDecodings(std::string s) {
        if (s.empty()) {
            return 0;
        }
        for (char digit : s) {
            if (digit < '0' || digit > '9') {
                throw std::invalid_argument("Input must contain decimal digits only");
            }
        }
        // Clipping each nonnegative state preserves every final value below cap.
        const std::int64_t cap = static_cast<std::int64_t>(std::numeric_limits<int>::max()) + 1;
        std::int64_t two_back = 1;
        std::int64_t previous = s.front() == '0' ? 0 : 1;
        for (std::size_t i = 1; i < s.size(); ++i) {
            std::int64_t current = s[i] == '0' ? 0 : previous;
            const int pair = (s[i - 1] - '0') * 10 + (s[i] - '0');
            if (pair >= 10 && pair <= 26) {
                current += two_back;
            }
            two_back = previous;
            previous = std::min(current, cap);
        }
        if (previous > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Final decoding count exceeds the problem guarantee");
        }
        return static_cast<int>(previous);
    }
};
}  // namespace lab
