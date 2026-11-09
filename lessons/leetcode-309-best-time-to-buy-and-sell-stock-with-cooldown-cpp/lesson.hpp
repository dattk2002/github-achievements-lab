#pragma once
#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>

namespace lab {
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) return 0;
        int held = -prices.front();
        int sold = std::numeric_limits<int>::min() / 4;
        int rest = 0;
        for (std::size_t day = 1; day < prices.size(); ++day) {
            // Read only yesterday's states: a sale cannot fund tomorrow's buy.
            const int next_held = std::max(held, rest - prices[day]);
            const int next_sold = held + prices[day];
            const int next_rest = std::max(rest, sold);
            held = next_held;
            sold = next_sold;
            rest = next_rest;
        }
        return std::max(rest, sold);
    }
};
}  // namespace lab
