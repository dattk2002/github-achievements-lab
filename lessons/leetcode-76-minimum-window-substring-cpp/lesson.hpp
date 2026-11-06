#pragma once

#include <array>
#include <string>

namespace lab {
class Solution {
public:
    std::string minWindow(std::string s, std::string t) {
        if (t.empty() || t.size() > s.size()) {
            return "";
        }
        std::array<int, 256> required{};
        for (unsigned char byte : t) {
            ++required[byte];
        }
        int missing = static_cast<int>(t.size());
        std::size_t left = 0;
        std::size_t best_start = 0;
        std::size_t best_length = s.size() + 1;
        for (std::size_t right = 0; right < s.size(); ++right) {
            const auto byte = static_cast<unsigned char>(s[right]);
            if (required[byte] > 0) {
                --missing;
            }
            --required[byte];
            while (missing == 0) {
                const std::size_t length = right - left + 1;
                if (length < best_length) {
                    best_start = left;
                    best_length = length;
                }
                const auto removed = static_cast<unsigned char>(s[left++]);
                ++required[removed];
                if (required[removed] > 0) {
                    ++missing;
                }
            }
        }
        return best_length > s.size() ? "" : s.substr(best_start, best_length);
    }
};
}  // namespace lab
