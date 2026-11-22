#pragma once

#include <string>

namespace lab {
class Solution {
public:
    // Preconditions: s has 1 to 100 characters, each either 'a' or 'b'.
    bool checkString(std::string s) {
        bool seen_b = false;
        for (char letter : s) {
            if (letter == 'b') {
                seen_b = true;
            } else if (seen_b) {
                return false;
            }
        }
        return true;
    }
};
}  // namespace lab
