#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: LeetCode 1882 bounds; both inputs remain unchanged.
    std::vector<int> assignTasks(std::vector<int>& servers, std::vector<int>& tasks) {
        using Free = std::pair<int, int>;  // weight, index
        using Busy = std::tuple<long long, int, int>;  // finish, weight, index
        std::priority_queue<Free, std::vector<Free>, std::greater<Free>> free;
        std::priority_queue<Busy, std::vector<Busy>, std::greater<Busy>> busy;
        for (std::size_t i = 0; i < servers.size(); ++i) {
            free.emplace(servers[i], static_cast<int>(i));
        }
        std::vector<int> answer;
        answer.reserve(tasks.size());
        long long time = 0;
        for (std::size_t j = 0; j < tasks.size(); ++j) {
            time = std::max(time, static_cast<long long>(j));
            if (free.empty()) time = std::max(time, std::get<0>(busy.top()));
            // Release the entire simultaneous batch before applying free priority.
            while (!busy.empty() && std::get<0>(busy.top()) <= time) {
                const auto [finish, weight, index] = busy.top();
                (void)finish;
                busy.pop();
                free.emplace(weight, index);
            }
            const auto [weight, index] = free.top();
            free.pop();
            answer.push_back(index);
            busy.emplace(time + tasks[j], weight, index);
        }
        return answer;
    }
};
}  // namespace lab
