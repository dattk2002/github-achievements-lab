#pragma once

#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: k and arrival.size() in [1, 100000]; equal array lengths;
    // strictly increasing arrival; arrival and load values in [1, 10^9].
    // Preserves both input arrays and returns IDs in increasing order.
    std::vector<int> busiestServers(int k, std::vector<int>& arrival,
                                    std::vector<int>& load) {
        std::set<int> available;
        for (int id = 0; id < k; ++id) available.insert(id);
        using Event = std::pair<long long, int>;
        std::priority_queue<Event, std::vector<Event>, std::greater<Event>> busy;
        std::vector<int> count(k, 0);
        for (int i = 0; i < static_cast<int>(arrival.size()); ++i) {
            // A server finishing exactly now can handle this request.
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }
            if (available.empty()) continue;
            auto chosen = available.lower_bound(i % k);
            if (chosen == available.end()) chosen = available.begin();
            const int id = *chosen;
            available.erase(chosen);
            ++count[id];
            busy.emplace(static_cast<long long>(arrival[i]) + load[i], id);
        }
        const int maximum = *std::max_element(count.begin(), count.end());
        std::vector<int> result;
        for (int id = 0; id < k; ++id) {
            if (count[id] == maximum) result.push_back(id);
        }
        return result;
    }
};
}  // namespace lab
