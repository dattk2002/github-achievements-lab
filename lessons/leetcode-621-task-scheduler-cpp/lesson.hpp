#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
        if (n < 0 || n > 100)
            throw std::invalid_argument("cooldown must be in [0,100]");
        std::array<int, 26> counts{};
        for (char task : tasks) {
            if (task < 'A' || task > 'Z')
                throw std::invalid_argument("task must be uppercase A..Z");
            ++counts[static_cast<std::size_t>(task - 'A')];
        }
        if (tasks.empty()) return 0;
        const int maximum = *std::max_element(counts.begin(), counts.end());
        const int tied = static_cast<int>(std::count(counts.begin(), counts.end(), maximum));
        const int frame = (maximum - 1) * (n + 1) + tied;
        return std::max(static_cast<int>(tasks.size()), frame);
    }
};
}  // namespace lab
