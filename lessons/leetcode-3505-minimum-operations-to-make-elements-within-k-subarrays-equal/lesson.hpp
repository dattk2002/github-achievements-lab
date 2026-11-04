#pragma once

#include <algorithm>
#include <iterator>
#include <limits>
#include <set>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: 2 <= n <= 100000, |nums[i]| <= 1000000,
    // 2 <= x <= n, 1 <= k <= 15, k*x <= n. Preserves nums.
    long long minOperations(std::vector<int>& nums, int x, int k) {
        const int n = static_cast<int>(nums.size());
        std::multiset<int> low, high;
        long long low_sum = 0, high_sum = 0;
        // low contains the smaller ceil(window_size/2) values.
        auto balance = [&]() {
            while (low.size() > high.size() + 1) {
                auto it = std::prev(low.end());
                const int value = *it;
                low_sum -= value;
                high_sum += value;
                high.insert(value);
                low.erase(it);
            }
            while (low.size() < high.size()) {
                auto it = high.begin();
                const int value = *it;
                high_sum -= value;
                low_sum += value;
                low.insert(value);
                high.erase(it);
            }
        };
        std::vector<long long> cost(n - x + 1);
        for (int i = 0; i < n; ++i) {
            const int value = nums[i];
            if (low.empty() || value <= *low.rbegin()) {
                low.insert(value);
                low_sum += value;
            } else {
                high.insert(value);
                high_sum += value;
            }
            balance();
            if (i >= x) {
                const int outgoing = nums[i - x];
                auto it = low.find(outgoing);
                if (it != low.end()) {
                    low.erase(it); // Erase one occurrence, not all duplicates.
                    low_sum -= outgoing;
                } else {
                    high.erase(high.find(outgoing));
                    high_sum -= outgoing;
                }
                balance();
            }
            if (i >= x - 1) {
                const long long median = *low.rbegin();
                cost[i - x + 1] = median * static_cast<long long>(low.size())
                    - low_sum + high_sum
                    - median * static_cast<long long>(high.size());
            }
        }

        const long long inf = std::numeric_limits<long long>::max() / 4;
        // previous[i]: exactly t-1 disjoint windows in the first i elements.
        std::vector<long long> previous(n + 1, 0), current(n + 1, inf);
        for (int t = 1; t <= k; ++t) {
            std::fill(current.begin(), current.end(), inf);
            for (int i = t * x; i <= n; ++i) {
                current[i] = std::min(current[i - 1],
                                      previous[i - x] + cost[i - x]);
            }
            previous.swap(current);
        }
        return previous[n];
    }
};
}  // namespace lab
