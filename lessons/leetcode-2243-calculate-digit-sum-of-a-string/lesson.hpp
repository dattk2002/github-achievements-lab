#pragma once

#include <algorithm>
#include <cstddef>
#include <string>

namespace lab {
class Solution {
public:
    // Preconditions: 1 <= s.size() <= 100, digits only, 2 <= k <= 100.
    std::string digitSum(std::string s, int k) {
        const auto width = static_cast<std::size_t>(k);
        while (s.size() > width) {
            std::string next;
            for (std::size_t start = 0; start < s.size(); start += width) {
                int sum = 0;
                const auto end = std::min(start + width, s.size());
                for (auto i = start; i < end; ++i) {
                    sum += s[i] - '0';
                }
                next += std::to_string(sum);
            }
            s.swap(next);
        }
        return s;
    }
};
}  // namespace lab
