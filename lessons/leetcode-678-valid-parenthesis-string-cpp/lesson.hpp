#pragma once
#include <algorithm>
#include <string>

namespace lab {
class Solution {
public:
    bool checkValidString(const std::string& s) {
        int low = 0;
        int high = 0;
        for (char ch : s) {
            if (ch == '(') {
                ++low;
                ++high;
            } else if (ch == ')') {
                --low;
                --high;
            } else {
                --low;
                ++high;
            }
            if (high < 0) return false;
            low = std::max(low, 0);
        }
        return low == 0;
    }
};
}  // namespace lab
