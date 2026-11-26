#pragma once

namespace lab {
class Solution {
public:
    // Precondition: 1 <= n <= 50.
    bool canAliceWin(int n) {
        int completed_turns = 0;
        for (int take = 10; take > 0 && n >= take; --take) {
            n -= take;
            ++completed_turns;
        }
        return completed_turns % 2 == 1;
    }
};
}  // namespace lab
