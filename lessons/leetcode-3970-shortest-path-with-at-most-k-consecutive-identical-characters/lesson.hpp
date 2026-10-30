#pragma once

#include <functional>
#include <limits>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: inputs satisfy the problem's graph, label and k limits.
    int shortestPath(int n, std::vector<std::vector<int>>& edges,
                     std::string labels, int k) {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
        }
        using Distance = long long;
        constexpr Distance infinity = std::numeric_limits<Distance>::max() / 4;
        std::vector<std::vector<Distance>> distance(
            n, std::vector<Distance>(k + 1, infinity));
        using State = std::tuple<Distance, int, int>;
        std::priority_queue<State, std::vector<State>, std::greater<State>> pending;
        distance[0][1] = 0;
        pending.emplace(0, 0, 1);
        while (!pending.empty()) {
            const auto [cost, u, run] = pending.top();
            pending.pop();
            if (cost != distance[u][run]) continue;
            if (u == n - 1) return static_cast<int>(cost);
            for (const auto& [v, weight] : graph[u]) {
                const int next = labels[u] == labels[v] ? run + 1 : 1;
                if (next > k) continue;
                const Distance candidate = cost + weight;
                if (candidate < distance[v][next]) {
                    distance[v][next] = candidate;
                    pending.emplace(candidate, v, next);
                }
            }
        }
        return -1;
    }
};
}  // namespace lab
