#pragma once
#include <algorithm>
#include <cstddef>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        auto sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        const auto visit = [&](auto&& self, std::size_t begin) -> void {
            result.push_back(path);
            for (std::size_t i = begin; i < sorted.size(); ++i) {
                if (i > begin && sorted[i] == sorted[i - 1]) continue;
                path.push_back(sorted[i]);
                self(self, i + 1);
                path.pop_back();
            }
        };
        visit(visit, 0);
        return result;
    }
};
}  // namespace lab
