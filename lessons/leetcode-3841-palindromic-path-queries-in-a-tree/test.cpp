#include "lesson.hpp"

#include <array>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace lab {
void check(int n, std::vector<std::vector<int>> edges, const std::string& s,
           std::vector<std::string> queries, const std::vector<bool>& wanted) {
    Solution solution;
    if (solution.palindromePath(n, edges, s, queries) != wanted) {
        std::cerr << "palindromePath failed: n=" << n << '\n';
        std::exit(EXIT_FAILURE);
    }
}

// Independent oracle: BFS finds the actual path, then counts all 26 letters.
std::vector<bool> brute(int n, const std::vector<std::vector<int>>& edges,
                       std::string s, const std::vector<std::string>& queries) {
    std::vector<std::vector<int>> graph(n);
    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }
    std::vector<bool> result;
    for (const auto& query : queries) {
        std::istringstream input(query);
        std::string operation;
        int u;
        input >> operation >> u;
        if (operation == "update") {
            input >> s[u];
            continue;
        }
        int v;
        input >> v;
        std::vector<int> previous(n, -1);
        std::queue<int> pending;
        previous[u] = u;
        pending.push(u);
        while (!pending.empty()) {
            const int node = pending.front();
            pending.pop();
            for (int next : graph[node]) {
                if (previous[next] == -1) {
                    previous[next] = node;
                    pending.push(next);
                }
            }
        }
        std::array<int, 26> counts{};
        for (int node = v;; node = previous[node]) {
            ++counts[s[node] - 'a'];
            if (node == u) break;
        }
        int odd = 0;
        for (int count : counts) odd += count % 2;
        result.push_back(odd <= 1);
    }
    return result;
}

void tests() {
    // Singleton, same-letter updates, update-only streams, and fresh calls.
    check(1, {}, "z", {"query 0 0", "update 0 a", "query 0 0"}, {true, true});
    check(1, {}, "a", {"update 0 z"}, {});
    check(2, {{1, 0}}, "az", {"query 0 1", "update 1 a", "query 1 0",
          "update 1 a", "query 0 1", "update 0 z", "query 1 0"},
          {false, true, true, false});
    // LCA at root and inside a branch; ancestor, reversed and singleton paths.
    const std::vector<std::vector<int>> edges{{0, 1}, {0, 2}, {1, 3}, {1, 4}};
    check(5, edges, "abcba", {"query 3 4", "query 3 2", "query 1 3",
          "update 1 a", "query 3 4", "query 0 4", "update 0 c",
          "query 4 2", "query 2 4", "query 1 1"},
          {true, false, true, true, true, true, true, true});
    // A palindrome need only be a permutation: abba is not required in order.
    check(4, {{0, 1}, {1, 2}, {2, 3}}, "aabb", {"query 0 3"}, {true});
    std::mt19937 random(3841);
    Solution reused;
    for (int trial = 0; trial < 180; ++trial) {
        const int n = 1 + static_cast<int>(random() % 30);
        std::vector<std::vector<int>> tree;
        for (int i = 1; i < n; ++i) tree.push_back({i, static_cast<int>(random() % i)});
        std::string s(n, 'a');
        for (char& c : s) c = static_cast<char>('a' + random() % 26);
        std::vector<std::string> queries;
        for (int step = 0; step < 200; ++step) {
            const auto u = std::to_string(random() % n);
            if (random() % 3 == 0) {
                queries.push_back("update " + u + " " + static_cast<char>('a' + random() % 26));
            } else {
                queries.push_back("query " + u + " " + std::to_string(random() % n));
            }
        }
        const auto wanted = brute(n, tree, s, queries);
        if (reused.palindromePath(n, tree, s, queries) != wanted) {
            std::cerr << "BFS differential test failed at trial " << trial << '\n';
            std::exit(EXIT_FAILURE);
        }
    }
    // Both maximum limits: repeated changes at the root must affect the far end.
    const int n = 50000;
    std::vector<std::vector<int>> chain;
    for (int i = 1; i < n; ++i) chain.push_back({i - 1, i});
    std::vector<std::string> queries;
    std::vector<bool> wanted;
    for (int i = 0; i < 25000; ++i) {
        queries.push_back(i % 2 == 0 ? "update 0 z" : "update 0 a");
        queries.push_back("query 0 49999");
        wanted.push_back(i % 2 != 0);
    }
    check(n, chain, std::string(n, 'a'), queries, wanted);
}
}  // namespace lab

int main() {
    lab::tests();
    std::cout << "palindromic path queries: all cases passed\n";
}
