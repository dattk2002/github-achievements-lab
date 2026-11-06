#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

namespace lab {
namespace {
void check(int n, std::vector<std::vector<int>> logs, int x,
           std::vector<int> queries, const std::vector<int>& expected) {
    const auto original_logs = logs;
    const auto original_queries = queries;
    Solution solution;
    const auto actual = solution.countServers(n, logs, x, queries);
    if (actual != expected || logs != original_logs || queries != original_queries) {
        std::cerr << "countServers failed: n=" << n << ", x=" << x << "\nexpected:";
        for (int value : expected) std::cerr << ' ' << value;
        std::cerr << "\nactual:";
        for (int value : actual) std::cerr << ' ' << value;
        std::cerr << "\nInputs must also remain unchanged.\n";
        std::exit(EXIT_FAILURE);
    }
}

// Independent oracle: scan every log anew for each query, without sorting.
std::vector<int> brute_force(int n, const std::vector<std::vector<int>>& logs,
                             int x, const std::vector<int>& queries) {
    std::vector<int> result;
    for (int query : queries) {
        std::vector<bool> seen(n + 1, false);
        for (const auto& log : logs) {
            if (query - x <= log[1] && log[1] <= query) seen[log[0]] = true;
        }
        int idle = 0;
        for (int server = 1; server <= n; ++server) idle += !seen[server];
        result.push_back(idle);
    }
    return result;
}
}  // namespace

void run_tests() {
    // Closed endpoints, logs just outside, unsorted and repeated queries.
    check(5, {{4, 11}, {2, 10}, {1, 6}, {3, 5}}, 4, {11, 10, 10, 20}, {3, 3, 3, 5});
    // Expiring one request must not deactivate a server with another live request.
    check(3, {{1, 2}, {1, 3}, {1, 3}, {2, 4}}, 2, {3, 4, 5, 6, 7}, {2, 1, 1, 2, 3});
    check(1, {{1, 1}}, 1, {2, 3}, {0, 1});
    check(2, {{2, 1000000}}, 100000, {100001, 1000000}, {2, 1});
    check(4, {{4, 8}, {2, 8}, {1, 8}, {3, 8}}, 1, {9, 8, 10}, {0, 0, 4});
    // A large query jump must remove logs older than the entire new window.
    check(3, {{1, 1}, {2, 20}, {3, 99}}, 2, {3, 100}, {2, 2});

    std::mt19937 random(2747);
    for (int trial = 0; trial < 2000; ++trial) {
        const int n = 1 + random() % 8;
        const int x = 1 + random() % 10;
        std::vector<std::vector<int>> logs;
        const int count = 1 + random() % 30;
        for (int i = 0; i < count; ++i) {
            logs.push_back({1 + static_cast<int>(random() % n),
                            1 + static_cast<int>(random() % 40)});
        }
        std::vector<int> queries;
        for (int i = 0; i < 20; ++i) queries.push_back(x + 1 + random() % 40);
        check(n, logs, x, queries, brute_force(n, logs, x, queries));
    }

    // Maximum n, log count, query count and time; every server appears twice.
    std::vector<std::vector<int>> logs;
    for (int server = 50000; server >= 1; --server) {
        logs.push_back({server, 900000});
        logs.push_back({server, 1000000});
    }
    check(100000, logs, 100000, std::vector<int>(100000, 1000000),
          std::vector<int>(100000, 50000));
    std::cout << "countServers: fixed boundaries, 2000 oracle cases and maximum-size case passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
