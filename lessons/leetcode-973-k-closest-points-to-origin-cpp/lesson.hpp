#pragma once
#include <cstddef>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        if (k < 1 || static_cast<std::size_t>(k) > points.size())
            throw std::invalid_argument("k must be in [1, points.size()]");
        for (const auto& point : points)
            if (point.size() != 2)
                throw std::invalid_argument("point must contain two coordinates");
        const auto count = static_cast<std::size_t>(k);
        std::priority_queue<std::pair<long long, std::size_t>> selected;
        for (std::size_t i = 0; i < points.size(); ++i) {
            const long long distance = 1LL * points[i][0] * points[i][0]
                                     + 1LL * points[i][1] * points[i][1];
            selected.emplace(distance, i);
            if (selected.size() > count) selected.pop();
        }
        std::vector<std::vector<int>> result;
        result.reserve(count);
        while (!selected.empty()) {
            result.push_back(points[selected.top().second]);
            selected.pop();
        }
        return result;
    }
};
}  // namespace lab
