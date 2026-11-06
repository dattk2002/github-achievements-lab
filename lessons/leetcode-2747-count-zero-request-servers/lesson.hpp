#pragma once

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: LeetCode 2747 bounds. Preserve both input arrays.
    std::vector<int> countServers(int n, std::vector<std::vector<int>>& logs,
                                  int x, std::vector<int>& queries) {
        auto ordered_logs = logs;
        std::sort(ordered_logs.begin(), ordered_logs.end(),
                  [](const auto& a, const auto& b) { return a[1] < b[1]; });
        std::vector<std::size_t> order(queries.size());
        std::iota(order.begin(), order.end(), std::size_t{0});
        std::sort(order.begin(), order.end(),
                  [&queries](std::size_t a, std::size_t b) {
                      return queries[a] < queries[b];
                  });

        std::vector<int> frequency(n + 1, 0);
        std::vector<int> answer(queries.size());
        std::size_t left = 0;
        std::size_t right = 0;
        int active = 0;
        for (std::size_t index : order) {
            const int end = queries[index];
            while (right < ordered_logs.size() && ordered_logs[right][1] <= end) {
                const int server = ordered_logs[right++][0];
                if (frequency[server]++ == 0) ++active;
            }
            // Strict inequality preserves requests at the inclusive lower bound.
            while (left < right && ordered_logs[left][1] < end - x) {
                const int server = ordered_logs[left++][0];
                if (--frequency[server] == 0) --active;
            }
            answer[index] = n - active;
        }
        return answer;
    }
};
}  // namespace lab
