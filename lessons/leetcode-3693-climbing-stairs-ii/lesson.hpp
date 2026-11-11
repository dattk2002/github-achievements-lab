#pragma once

#include <algorithm>
#include <array>
#include <limits>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: 1 <= n == costs.size() <= 100000;
    // 1 <= costs[i] <= 10000. Preserves costs.
    int climbStairs(int n, std::vector<int>& costs) {
        std::array<int, 3> recent{};
        for (int step = 1; step <= n; ++step) {
            int best = std::numeric_limits<int>::max();
            for (int jump = 1; jump <= 3 && jump <= step; ++jump) {
                best = std::min(best, recent[(step - jump) % 3]
                                         + costs[step - 1] + jump * jump);
            }
            // All predecessors have been read before overwriting step - 3.
            recent[step % 3] = best;
        }
        return recent[n % 3];
    }
};
}  // namespace lab
