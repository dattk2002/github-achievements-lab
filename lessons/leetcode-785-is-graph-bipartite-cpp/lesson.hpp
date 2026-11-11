#pragma once
#include <cstddef>
#include <queue>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    bool isBipartite(std::vector<std::vector<int>>& graph) {
        for (const auto& neighbors : graph)
            for (int neighbor : neighbors)
                if (neighbor < 0 || static_cast<std::size_t>(neighbor) >= graph.size())
                    throw std::invalid_argument("neighbor index out of range");
        std::vector<int> color(graph.size(), -1);
        std::queue<std::size_t> pending;
        for (std::size_t start = 0; start < graph.size(); ++start) {
            if (color[start] != -1) continue;
            color[start] = 0;
            pending.push(start);
            while (!pending.empty()) {
                const std::size_t node = pending.front();
                pending.pop();
                for (int neighbor : graph[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        pending.push(static_cast<std::size_t>(neighbor));
                    } else if (color[neighbor] == color[node]) return false;
                }
            }
        }
        return true;
    }
};
}  // namespace lab
