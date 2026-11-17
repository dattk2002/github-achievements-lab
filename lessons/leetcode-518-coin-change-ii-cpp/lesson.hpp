#pragma once
#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int change(int amount, std::vector<int>& coins) {
        if (amount < 0) throw std::invalid_argument("amount must be nonnegative");
        auto denominations = coins;
        std::sort(denominations.begin(), denominations.end());
        for (std::size_t i = 0; i < denominations.size(); ++i) {
            if (denominations[i] <= 0 || (i > 0 && denominations[i] == denominations[i - 1]))
                throw std::invalid_argument("denominations must be positive and unique");
        }
        // The final answer may fit int even when unrelated subtotals do not.
        const long long cap = static_cast<long long>(std::numeric_limits<int>::max()) + 1;
        std::vector<long long> ways(static_cast<std::size_t>(amount) + 1, 0);
        ways[0] = 1;
        for (int coin : denominations) {
            for (std::size_t sum = static_cast<std::size_t>(coin); sum < ways.size(); ++sum)
                ways[sum] = std::min(cap, ways[sum] + ways[sum - coin]);
        }
        if (ways[amount] == cap) throw std::overflow_error("combination count exceeds int");
        return static_cast<int>(ways[amount]);
    }
};
}  // namespace lab
