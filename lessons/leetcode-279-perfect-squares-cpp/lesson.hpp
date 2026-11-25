#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int numSquares(int n) {
        if (n < 0 || n > 10000) throw std::invalid_argument("n must be in [0,10000]");
        std::vector<int> best(static_cast<std::size_t>(n + 1), n + 1);
        best[0] = 0;
        for (int sum = 1; sum <= n; ++sum) {
            for (int root = 1; root * root <= sum; ++root) {
                best[sum] = std::min(best[sum], best[sum - root * root] + 1);
            }
        }
        return best[n];
    }
};
}  // namespace lab
