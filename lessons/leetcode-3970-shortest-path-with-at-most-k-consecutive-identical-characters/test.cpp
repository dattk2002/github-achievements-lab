#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace lab {
void check(const std::string& name, int n, std::vector<std::vector<int>> edges,
           const std::string& labels, int k, int expected) {
    const auto original = edges;
    Solution solution;
    const int actual = solution.shortestPath(n, edges, labels, k);
    if (actual != expected || edges != original ||
        solution.shortestPath(n, edges, labels, k) != expected) {
        std::cerr << name << ": expected " << expected << ", got " << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}

// Independent oracle: enumerate reachable states by exact integer cost, no heap.
int costOracle(int n, const std::vector<std::vector<int>>& edges,
               const std::string& labels, int k) {
    // A cheapest expanded-state path is simple: at most n*k-1 edges, weight <=3.
    const int budget = 3 * (n * k - 1);
    std::vector<std::vector<std::vector<bool>>> reachable(
        budget + 1, std::vector<std::vector<bool>>(n, std::vector<bool>(k + 1)));
    reachable[0][0][1] = true;
    for (int cost = 0; cost <= budget; ++cost) {
        for (int run = 1; run <= k; ++run) {
            if (reachable[cost][n - 1][run]) return cost;
        }
        for (const auto& edge : edges) {
            if (cost + edge[2] > budget) continue;
            for (int run = 1; run <= k; ++run) {
                const int next = labels[edge[0]] == labels[edge[1]] ? run + 1 : 1;
                if (next <= k && reachable[cost][edge[0]][run]) {
                    reachable[cost + edge[2]][edge[1]][next] = true;
                }
            }
        }
    }
    return -1;
}

void tests() {
    check("single vertex counts once", 1, {}, "z", 1, 0);
    check("no edges", 2, {}, "ab", 50, -1);
    check("direction matters", 2, {{1, 0, 2}}, "ab", 1, -1);
    check("first label counts", 2, {{0, 1, 2}}, "aa", 1, -1);
    check("exact run limit", 4, {{0, 1, 2}, {1, 2, 3}, {2, 3, 4}}, "aaab", 3, 9);
    check("one beyond limit", 4, {{0, 1, 2}, {1, 2, 3}, {2, 3, 4}}, "aaab", 2, -1);
    check("valid detour", 4, {{0, 1, 1}, {1, 3, 1}, {0, 2, 4}, {2, 3, 3}},
          "aaba", 1, 7);
    // Arriving at 2 cheaply with run 2 cannot use 2->3; run 1 can.
    check("retain different runs", 4,
          {{0, 2, 1}, {0, 1, 2}, {1, 2, 2}, {2, 3, 1}}, "abaa", 2, 5);
    // The only feasible walk revisits 1 after resetting its run at 2.
    check("reset cycle is necessary", 4,
          {{0, 1, 1}, {1, 2, 2}, {2, 1, 2}, {1, 3, 1}}, "aaba", 2, 6);
    check("positive unreachable cycle", 4, {{0, 1, 1}, {1, 0, 1}}, "abab", 1, -1);
    check("parallel edges and weighted choice", 3,
          {{0, 2, 20}, {0, 1, 8}, {0, 1, 2}, {1, 2, 3}}, "abc", 1, 5);
    check("stale heap entries", 4,
          {{0, 1, 9}, {0, 2, 1}, {2, 1, 1}, {1, 3, 20}}, "abcd", 1, 22);

    std::mt19937 random(3970);
    for (int trial = 0; trial < 250; ++trial) {
        const int n = 1 + random() % 6;
        const int k = 1 + random() % 3;
        std::string labels(n, 'a');
        for (char& c : labels) c = static_cast<char>('a' + random() % 3);
        std::vector<std::vector<int>> edges;
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (u != v && random() % 3 == 0) {
                    edges.push_back({u, v, static_cast<int>(1 + random() % 3)});
                }
            }
        }
        check("cost oracle trial " + std::to_string(trial), n, edges, labels, k,
              costOracle(n, edges, labels, k));
    }

    std::vector<std::vector<int>> chain;
    for (int i = 0; i < 49; ++i) chain.push_back({i, i + 1, 1});
    check("k maximum inclusive", 50, chain, std::string(50, 'a'), 50, 49);
    chain.push_back({49, 50, 1});
    check("k maximum exceeded", 51, chain, std::string(51, 'a'), 50, -1);

    chain.clear();
    std::string labels(50000, 'a');
    for (int i = 0; i < 50000; ++i) {
        labels[i] = (i % 2 == 0 ? 'a' : 'b');
        if (i > 0) chain.push_back({i - 1, i, 10000});
    }
    check("maximum nodes and weights", 50000, chain, labels, 50, 499990000);
    chain.push_back({49999, 0, 10000});
    labels.assign(50000, 'a');
    check("maximum edges blocked run", 50000, chain, labels, 50, -1);
}
}  // namespace lab

int main() {
    lab::tests();
    std::cout << "All shortestPath tests passed\n";
}
