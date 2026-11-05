#pragma once

#include <vector>

namespace lab {
class Solution {
    static void extend(const std::vector<int>& nums, std::vector<bool>& used,
                       std::vector<int>& path, std::vector<std::vector<int>>& result) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (std::size_t i = 0; i < nums.size(); ++i) {
            if (used[i]) {
                continue;
            }
            used[i] = true;
            path.push_back(nums[i]);
            extend(nums, used, path, result);
            path.pop_back();
            used[i] = false;
        }
    }

public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<bool> used(nums.size(), false);
        std::vector<int> path;
        path.reserve(nums.size());
        extend(nums, used, path, result);
        return result;
    }
};
}  // namespace lab
