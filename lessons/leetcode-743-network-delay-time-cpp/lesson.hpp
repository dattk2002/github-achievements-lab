#pragma once

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
        if (n <= 0 || k < 1 || k > n) {
            throw std::invalid_argument("Invalid node count or source");
        }
        std::vector<std::vector<std::pair<int, int>>> outgoing(static_cast<std::size_t>(n) + 1);
        for (const auto& edge : times) {
            if (edge.size() != 3 || edge[0] < 1 || edge[0] > n ||
                edge[1] < 1 || edge[1] > n || edge[2] < 0) {
                throw std::invalid_argument("Invalid directed weighted edge");
            }
            outgoing[edge[0]].emplace_back(edge[1], edge[2]);
        }
        const int infinity = std::numeric_limits<int>::max() / 4;
        std::vector<int> distance(static_cast<std::size_t>(n) + 1, infinity);
        using Entry = std::pair<int, int>;
        std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> ready;
        distance[k] = 0;
        ready.emplace(0, k);
        while (!ready.empty()) {
            const auto [cost, node] = ready.top();
            ready.pop();
            if (cost != distance[node]) {
                continue;
            }
            for (const auto& [next, weight] : outgoing[node]) {
                const int candidate = cost + weight;
                if (candidate < distance[next]) {
                    distance[next] = candidate;
                    ready.emplace(candidate, next);
                }
            }
        }
        int maximum = 0;
        for (int node = 1; node <= n; ++node) {
            if (distance[node] == infinity) {
                return -1;
            }
            maximum = std::max(maximum, distance[node]);
        }
        return maximum;
    }
};
}  // namespace lab
