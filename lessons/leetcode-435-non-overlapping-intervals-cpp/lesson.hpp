#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        for (const auto& interval : intervals) {
            if (interval.size() != 2 || interval[0] >= interval[1])
                throw std::invalid_argument("interval must contain start < end");
        }
        if (intervals.empty()) return 0;
        auto ordered = intervals;
        std::sort(ordered.begin(), ordered.end(), [](const auto& a, const auto& b) {
            if (a[1] != b[1]) return a[1] < b[1];
            return a[0] < b[0];
        });
        int kept = 1;
        int last_end = ordered.front()[1];
        for (std::size_t i = 1; i < ordered.size(); ++i) {
            if (ordered[i][0] >= last_end) {
                ++kept;
                last_end = ordered[i][1];
            }
        }
        return static_cast<int>(ordered.size()) - kept;
    }
};
}  // namespace lab
