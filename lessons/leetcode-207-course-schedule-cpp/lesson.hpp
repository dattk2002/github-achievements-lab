#pragma once

#include <queue>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        if (numCourses <= 0) {
            throw std::invalid_argument("Course count must be positive");
        }
        std::vector<std::vector<int>> outgoing(static_cast<std::size_t>(numCourses));
        std::vector<int> indegree(static_cast<std::size_t>(numCourses), 0);
        for (const auto& edge : prerequisites) {
            if (edge.size() != 2 || edge[0] < 0 || edge[0] >= numCourses ||
                edge[1] < 0 || edge[1] >= numCourses) {
                throw std::invalid_argument("Invalid prerequisite edge");
            }
            outgoing[edge[1]].push_back(edge[0]);
            ++indegree[edge[0]];
        }
        std::queue<int> ready;
        for (int course = 0; course < numCourses; ++course) {
            if (indegree[course] == 0) {
                ready.push(course);
            }
        }
        int completed = 0;
        while (!ready.empty()) {
            const int course = ready.front();
            ready.pop();
            ++completed;
            for (int next : outgoing[course]) {
                --indegree[next];
                if (indegree[next] == 0) {
                    ready.push(next);
                }
            }
        }
        return completed == numCourses;
    }
};
}  // namespace lab
