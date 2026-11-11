#pragma once

#include <algorithm>

namespace lab {
class Solution {
public:
    // Preconditions: costs in [1, 1000000], needs in [0, 1000000000].
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {
        const long long n1 = need1;
        const long long n2 = need2;
        const auto cost = [&](long long both) {
            return both * costBoth + std::max(0LL, n1 - both) * cost1
                                   + std::max(0LL, n2 - both) * cost2;
        };
        return std::min({cost(0), cost(std::min(n1, n2)),
                        cost(std::max(n1, n2))});
    }
};
}  // namespace lab
