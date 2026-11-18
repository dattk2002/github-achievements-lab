#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m < 1 || m > 100 || n < 1 || n > 100)
            throw std::invalid_argument("dimensions must be in [1,100]");
        if (m < n) std::swap(m, n);
        // Saturation preserves whether the final count exceeds the contract.
        constexpr long long cap = 2000000001LL;
        std::vector<long long> paths(n, 1);
        for (int row = 1; row < m; ++row)
            for (int col = 1; col < n; ++col)
                paths[col] = std::min(cap, paths[col] + paths[col - 1]);
        if (paths.back() == cap)
            throw std::overflow_error("path count exceeds 2000000000");
        return static_cast<int>(paths.back());
    }
};
}  // namespace lab
