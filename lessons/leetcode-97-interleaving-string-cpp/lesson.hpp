#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {
        if (s1.size() + s2.size() != s3.size()) return false;
        if (s1.size() < s2.size()) std::swap(s1, s2);
        std::vector<unsigned char> possible(s2.size() + 1, 0);
        possible[0] = 1;
        for (std::size_t j = 1; j <= s2.size(); ++j)
            possible[j] = possible[j-1] && s2[j-1] == s3[j-1];
        for (std::size_t i = 1; i <= s1.size(); ++i) {
            possible[0] = possible[0] && s1[i-1] == s3[i-1];
            for (std::size_t j = 1; j <= s2.size(); ++j) {
                const char next = s3[i+j-1];
                possible[j] = (possible[j] && s1[i-1] == next) ||
                              (possible[j-1] && s2[j-1] == next);
            }
        }
        return possible.back() != 0;
    }
};
}  // namespace lab
