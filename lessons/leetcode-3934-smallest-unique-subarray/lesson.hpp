#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

namespace lab {
class Solution {
    static std::vector<int> suffixOrder(const std::vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        const int size = n + 1;
        std::vector<int> order(size), rank(size), shifted(size), nextRank(size), count(size);

        // Position n represents a sentinel smaller than every input value.
        order.front() = n;
        std::iota(order.begin() + 1, order.end(), 0);
        std::sort(order.begin() + 1, order.end(),
                  [&](int left, int right) { return nums[left] < nums[right]; });
        int classes = 2;
        rank[order[1]] = 1;
        for (int i = 2; i < size; ++i) {
            if (nums[order[i]] != nums[order[i - 1]]) {
                ++classes;
            }
            rank[order[i]] = classes - 1;
        }

        for (int width = 1; width < size && classes < size; width *= 2) {
            // Shifting starts back orders the pairs by their second rank.
            for (int i = 0; i < size; ++i) {
                shifted[i] = (order[i] + size - width) % size;
            }
            std::fill(count.begin(), count.begin() + classes, 0);
            for (int start : shifted) {
                ++count[rank[start]];
            }
            for (int r = 1; r < classes; ++r) {
                count[r] += count[r - 1];
            }
            // Stable counting sort by the first rank.
            for (auto it = shifted.rbegin(); it != shifted.rend(); ++it) {
                order[--count[rank[*it]]] = *it;
            }

            classes = 1;
            nextRank[order.front()] = 0;
            for (int i = 1; i < size; ++i) {
                const int left = order[i - 1];
                const int right = order[i];
                if (rank[left] != rank[right] ||
                    rank[(left + width) % size] != rank[(right + width) % size]) {
                    ++classes;
                }
                nextRank[right] = classes - 1;
            }
            rank.swap(nextRank);
        }

        order.erase(order.begin());
        return order;
    }

public:
    // Requires 1 <= nums.size() <= 100000 and 1 <= nums[i] <= 100000.
    int smallestUniqueSubarray(std::vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        const auto order = suffixOrder(nums);
        std::vector<int> position(n), lcp(n + 1);
        for (int i = 0; i < n; ++i) {
            position[order[i]] = i;
        }

        // Kasai's algorithm: lcp[r] compares ranks r - 1 and r.
        int matched = 0;
        for (int start = 0; start < n; ++start) {
            const int r = position[start];
            if (r == 0) {
                matched = 0;
                continue;
            }
            const int previous = order[r - 1];
            while (start + matched < n && previous + matched < n &&
                   nums[start + matched] == nums[previous + matched]) {
                ++matched;
            }
            lcp[r] = matched;
            if (matched > 0) {
                --matched;
            }
        }

        int best = n;
        for (int r = 0; r < n; ++r) {
            const int length = 1 + std::max(lcp[r], lcp[r + 1]);
            if (length <= n - order[r]) {
                best = std::min(best, length);
            }
        }
        return best;
    }
};
}  // namespace lab
