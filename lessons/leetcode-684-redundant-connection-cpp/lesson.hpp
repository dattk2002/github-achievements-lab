#pragma once

#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lab {
class Solution {
    static int find(std::vector<int>& parent, int node) {
        while (parent[node] != node) {
            parent[node] = parent[parent[node]];
            node = parent[node];
        }
        return node;
    }

public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
        if (edges.empty()) {
            return {};
        }
        const int n = static_cast<int>(edges.size());
        for (const auto& edge : edges) {
            if (edge.size() != 2 || edge[0] < 1 || edge[0] > n || edge[1] < 1 || edge[1] > n) {
                throw std::invalid_argument("Invalid edge shape or endpoint");
            }
        }
        std::vector<int> parent(static_cast<std::size_t>(n) + 1);
        std::iota(parent.begin(), parent.end(), 0);
        std::vector<int> size(static_cast<std::size_t>(n) + 1, 1);
        for (const auto& edge : edges) {
            int first = find(parent, edge[0]);
            int second = find(parent, edge[1]);
            if (first == second) {
                return edge;
            }
            if (size[first] < size[second]) {
                std::swap(first, second);
            }
            parent[second] = first;
            size[first] += size[second];
        }
        return {};
    }
};
}  // namespace lab
