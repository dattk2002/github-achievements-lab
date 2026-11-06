#pragma once

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        if (word1.size() < word2.size()) {
            std::swap(word1, word2);
        }
        std::vector<int> previous(word2.size() + 1);
        std::vector<int> current(word2.size() + 1);
        std::iota(previous.begin(), previous.end(), 0);
        for (std::size_t i = 1; i <= word1.size(); ++i) {
            current[0] = static_cast<int>(i);
            for (std::size_t j = 1; j <= word2.size(); ++j) {
                const int substitution = previous[j - 1] + (word1[i - 1] != word2[j - 1]);
                current[j] = std::min({previous[j] + 1, current[j - 1] + 1, substitution});
            }
            previous.swap(current);
        }
        return previous.back();
    }
};
}  // namespace lab
