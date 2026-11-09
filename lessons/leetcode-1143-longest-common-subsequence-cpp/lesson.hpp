#pragma once
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        if (text1.size() < text2.size()) std::swap(text1, text2);
        std::vector<int> previous(text2.size() + 1, 0);
        std::vector<int> current(text2.size() + 1, 0);
        for (char first : text1) {
            current[0] = 0;
            for (std::size_t j = 1; j <= text2.size(); ++j) {
                if (first == text2[j-1]) current[j] = previous[j-1] + 1;
                else current[j] = std::max(previous[j], current[j-1]);
            }
            previous.swap(current);
        }
        return previous.back();
    }
};
}  // namespace lab
