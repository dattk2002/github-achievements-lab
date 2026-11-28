#pragma once
#include <algorithm>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    int maximumSaleItems(std::vector<std::vector<int>>& items, int budget) {
        const int n = static_cast<int>(items.size());
        std::vector<int> frequency(n + 1, 0), multiples(n + 1, 0);
        int cheapest = items[0][1];
        for (const auto& item : items) {
            ++frequency[item[0]];
            cheapest = std::min(cheapest, item[1]);
        }
        for (int factor = 1; factor <= n; ++factor)
            for (int multiple = factor; multiple <= n; multiple += factor)
                multiples[factor] += frequency[multiple];

        std::vector<std::pair<int,int>> offers;
        offers.reserve(items.size());
        for (const auto& item : items)
            offers.emplace_back(item[1], multiples[item[0]] - 1);
        std::sort(offers.begin(), offers.end());

        long long total = 0;
        for (const auto& offer : offers) {
            const int price = offer.first;
            if (price > 2LL * cheapest) break;
            // Each of these copies can use a distinct outgoing gift pair.
            const int copies = std::min(offer.second, budget / price);
            total += 2LL * copies;
            budget -= copies * price;  // Product is bounded by remaining budget.
        }
        total += budget / cheapest;
        return static_cast<int>(total); // At most 2 * original budget <= 2e9.
    }
};
}  // namespace lab
