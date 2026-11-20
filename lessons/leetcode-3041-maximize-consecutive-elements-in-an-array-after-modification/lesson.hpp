#pragma once

#include <algorithm>
#include <map>
#include <vector>

namespace lab {
class Solution {
public:
    int maxSelectedElements(std::vector<int>& nums) {
        auto sorted = nums;
        std::sort(sorted.begin(), sorted.end());

        std::map<int, int> longest;
        int answer = 0;
        for (const int value : sorted) {
            int& increased = longest[value + 1];
            int& unchanged = longest[value];

            // Extend with value + 1 before updating the predecessor at value.
            increased = std::max(increased, unchanged + 1);
            unchanged = std::max(unchanged, longest[value - 1] + 1);
            answer = std::max({answer, increased, unchanged});
        }
        return answer;
    }
};
}  // namespace lab
