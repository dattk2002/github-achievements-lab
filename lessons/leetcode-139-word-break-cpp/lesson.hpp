#pragma once

#include <string>
#include <vector>

namespace lab {
class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        std::vector<bool> reachable(s.size() + 1, false);
        reachable[0] = true;
        for (std::size_t end = 1; end <= s.size(); ++end) {
            for (const auto& word : wordDict) {
                if (word.size() <= end && reachable[end - word.size()] &&
                    s.compare(end - word.size(), word.size(), word) == 0) {
                    reachable[end] = true;
                    break;
                }
            }
        }
        return reachable.back();
    }
};
}  // namespace lab
