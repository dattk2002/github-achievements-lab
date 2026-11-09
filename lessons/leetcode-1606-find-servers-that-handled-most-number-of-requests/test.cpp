#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

namespace lab {
namespace {
// Direct circular scan: deliberately no ordered set or event heap.
std::vector<int> simulate(int k, const std::vector<int>& arrival,
                          const std::vector<int>& load) {
    std::vector<long long> finish(k, 0);
    std::vector<int> count(k, 0);
    for (int i = 0; i < static_cast<int>(arrival.size()); ++i) {
        for (int offset = 0; offset < k; ++offset) {
            const int server = (i + offset) % k;
            if (finish[server] <= arrival[i]) {
                finish[server] = static_cast<long long>(arrival[i]) + load[i];
                ++count[server];
                break;
            }
        }
    }
    std::vector<int> result;
    const int maximum = *std::max_element(count.begin(), count.end());
    for (int server = 0; server < k; ++server) {
        if (count[server] == maximum) result.push_back(server);
    }
    return result;
}

void check(const std::string& name, int k, std::vector<int> arrival,
           std::vector<int> load, std::vector<int> expected) {
    const auto original_arrival = arrival;
    const auto original_load = load;
    static Solution solution;  // Reuse also checks that calls retain no state.
    auto actual = solution.busiestServers(k, arrival, load);
    std::sort(actual.begin(), actual.end());
    std::sort(expected.begin(), expected.end());
    if (actual != expected || arrival != original_arrival || load != original_load) {
        std::cerr << "FAIL: " << name << " expected IDs:";
        for (int id : expected) std::cerr << ' ' << id;
        std::cerr << "; actual IDs:";
        for (int id : actual) std::cerr << ' ' << id;
        std::cerr << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}  // namespace

void run_tests() {
    check("one request", 1, {1}, {1}, {0});
    check("unused servers are not busiest", 5, {7}, {9}, {0});
    check("single server drops then reuses at equality", 1,
          {1, 2, 5, 6}, {4, 1, 1, 1}, {0});
    // Assignments: 0, 1, 2, 0, 0; last request wraps from preferred ID 1.
    check("wrap to smaller ID", 3, {1, 2, 3, 4, 5}, {3, 10, 10, 1, 1}, {0});
    check("release every simultaneous completion", 3,
          {1, 2, 3, 6, 7, 8}, {5, 4, 3, 20, 20, 20}, {0, 1, 2});
    check("skip busy preferred server", 3,
          {2, 4, 6, 8, 10}, {20, 1, 20, 1, 1}, {1});
    check("all busy drops", 2, {1, 2, 3, 4, 5}, {100, 100, 1, 1, 1}, {0, 1});
    check("large times", 2, {1, 999999999, 1000000000},
          {1000000000, 1000000000, 1000000000}, {0, 1});

    std::mt19937 random(1606);
    for (int trial = 0; trial < 3000; ++trial) {
        const int k = 1 + static_cast<int>(random() % 8);
        const int n = 1 + static_cast<int>(random() % 40);
        std::vector<int> arrival(n), load(n);
        int time = 0;
        for (int i = 0; i < n; ++i) {
            time += 1 + static_cast<int>(random() % 5);
            arrival[i] = time;
            load[i] = 1 + static_cast<int>(random() % 30);
        }
        check("scan oracle trial " + std::to_string(trial), k, arrival, load,
              simulate(k, arrival, load));
    }

    const int limit = 100000;
    std::vector<int> arrival(limit), load(limit, 1000000000), all_ids(limit);
    std::iota(arrival.begin(), arrival.end(), 1);
    std::iota(all_ids.begin(), all_ids.end(), 0);
    check("maximum k and n, every server handles once", limit, arrival, load, all_ids);
    check("maximum n with all but first dropped", 1, arrival, load, {0});
    std::fill(load.begin(), load.end(), 1);
    check("maximum n with continuous reuse", 7, arrival, load, {0, 1, 2, 3, 4});
    std::cout << "busiest servers: boundary cases and 3000 scan comparisons passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
