#pragma once

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace lab {

class Solution {
public:
    // Preconditions: a valid tree and valid commands within the stated limits.
    std::vector<bool> palindromePath(int n, std::vector<std::vector<int>>& edges,
                                     std::string s, std::vector<std::string>& queries) {
        using Mask = std::uint32_t;
        const auto bit = [](char c) -> Mask { return Mask{1} << (c - 'a'); };
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int levels = 1;
        while ((1 << levels) <= n) ++levels;
        std::vector<std::vector<int>> up(levels, std::vector<int>(n));
        std::vector<int> tin(n), tout(n), depth(n), stack{0};
        std::vector<Mask> initial(n);
        initial[0] = bit(s[0]);
        int timer = 0;
        // Negative tokens mark exits. Every subtree occupies [tin, tout).
        while (!stack.empty()) {
            const int token = stack.back();
            stack.pop_back();
            if (token < 0) {
                tout[-token - 1] = timer;
                continue;
            }
            const int u = token;
            tin[u] = timer++;
            for (int level = 1; level < levels; ++level) {
                up[level][u] = up[level - 1][up[level - 1][u]];
            }
            stack.push_back(-u - 1);
            for (int v : graph[u]) {
                if (v == up[0][u]) continue;
                up[0][v] = u;
                depth[v] = depth[u] + 1;
                initial[v] = initial[u] ^ bit(s[v]);
                stack.push_back(v);
            }
        }
        const auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) {
                const int temporary = u;
                u = v;
                v = temporary;
            }
            const int difference = depth[u] - depth[v];
            for (int level = 0; level < levels; ++level) {
                if (difference & (1 << level)) u = up[level][u];
            }
            if (u == v) return u;
            for (int level = levels - 1; level >= 0; --level) {
                if (up[level][u] != up[level][v]) {
                    u = up[level][u];
                    v = up[level][v];
                }
            }
            return up[0][u];
        };
        std::vector<Mask> fenwick(n + 1);
        const auto toggle = [&](int position, Mask delta) {
            for (int i = position + 1; i <= n; i += i & -i) fenwick[i] ^= delta;
        };
        const auto prefix = [&](int u) {
            Mask result = initial[u];
            for (int i = tin[u] + 1; i > 0; i -= i & -i) result ^= fenwick[i];
            return result;
        };
        std::vector<bool> answer;
        for (const auto& query : queries) {
            std::istringstream input(query);
            std::string operation;
            int u;
            input >> operation >> u;
            if (operation == "update") {
                char c;
                input >> c;
                const Mask delta = bit(s[u]) ^ bit(c);
                toggle(tin[u], delta);
                toggle(tout[u], delta);
                s[u] = c;
            } else {
                int v;
                input >> v;
                const Mask mask = prefix(u) ^ prefix(v) ^ bit(s[lca(u, v)]);
                answer.push_back((mask & (mask - Mask{1})) == 0);
            }
        }
        return answer;
    }
};

}  // namespace lab
