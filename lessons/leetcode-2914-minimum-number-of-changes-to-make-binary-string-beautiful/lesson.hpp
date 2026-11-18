#pragma once

#include <string>

namespace lab {
class Solution {
public:
    // Preconditions: s contains only '0' and '1' and has even length in [2, 100000].
    int minChanges(std::string s) {
        int changes = 0;
        for (std::size_t i = 0; i < s.size(); i += 2) {
            if (s[i] != s[i + 1]) {
                ++changes;
            }
        }
        return changes;
    }
};
}  // namespace lab
