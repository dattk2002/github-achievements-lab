#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace lab {
namespace {
void check(const std::string& name, std::vector<int> servers,
           std::vector<int> tasks, const std::vector<int>& expected) {
    const auto saved_servers = servers;
    const auto saved_tasks = tasks;
    Solution solution;
    const auto actual = solution.assignTasks(servers, tasks);
    if (actual != expected || servers != saved_servers || tasks != saved_tasks) {
        std::cerr << "FAIL: " << name << " (answer or input preservation)\n";
        std::exit(EXIT_FAILURE);
    }
}

// Independent small-case oracle: advance one second at a time and scan servers.
std::vector<int> simulate(const std::vector<int>& servers,
                          const std::vector<int>& tasks) {
    std::vector<int> available_at(servers.size(), 0);
    std::vector<int> answer;
    std::size_t next = 0;
    for (int time = 0; next < tasks.size(); ++time) {
        while (next < tasks.size() && static_cast<int>(next) <= time) {
            int best = -1;
            for (std::size_t i = 0; i < servers.size(); ++i) {
                if (available_at[i] <= time &&
                    (best == -1 || servers[i] < servers[best] ||
                     (servers[i] == servers[best] && static_cast<int>(i) < best))) {
                    best = static_cast<int>(i);
                }
            }
            if (best == -1) break;
            available_at[best] = time + tasks[next++];
            answer.push_back(best);
        }
    }
    return answer;
}
}  // namespace

void run_tests() {
    check("minimum input", {1}, {1}, {0});
    check("one server backlog", {200000}, {200000, 1, 3, 2}, {0, 0, 0, 0});
    check("idle server waits for arrival", {7, 2}, {1, 1, 1, 1}, {1, 1, 1, 1});
    check("weight before index", {9, 4, 1}, {8, 8, 8}, {2, 1, 0});
    check("equal weights use index", {2, 2, 2}, {5, 5, 5, 1}, {0, 1, 2, 0});
    // Both finish at 4: release ALL before choosing the lighter server.
    check("simultaneous release and FIFO backlog", {5, 1}, {4, 3, 1, 1, 1},
          {1, 0, 1, 0, 1});
    check("release exactly at arrival", {1, 2}, {2, 4, 1, 1}, {0, 1, 0, 0});

    std::mt19937 random(1882);
    for (int trial = 0; trial < 2000; ++trial) {
        std::vector<int> servers(1 + random() % 6);
        std::vector<int> tasks(1 + random() % 25);
        for (int& weight : servers) weight = 1 + random() % 5;
        for (int& duration : tasks) duration = 1 + random() % 9;
        check("tick oracle " + std::to_string(trial), servers, tasks,
              simulate(servers, tasks));
    }

    // Equal durations: starts alternate; completion times reach 20 billion.
    std::vector<int> alternating(200000);
    for (int j = 0; j < 200000; ++j) alternating[j] = j % 2;
    check("64-bit completion times", {1, 1}, std::vector<int>(200000, 200000),
          alternating);
    check("maximum accumulated time", {1}, std::vector<int>(200000, 200000),
          std::vector<int>(200000, 0));
    std::vector<int> weights(200000, 200000);
    weights.back() = 1;
    check("maximum server count", weights, std::vector<int>(200000, 1),
          std::vector<int>(200000, 199999));
    std::cout << "assignTasks: fixed cases, 2000 oracle cases, maximum bounds passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
