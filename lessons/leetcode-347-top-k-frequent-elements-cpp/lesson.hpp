#pragma once
#include <cstddef>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, std::size_t> frequency;
        for (int value : nums) ++frequency[value];
        if (k < 0 || static_cast<std::size_t>(k) > frequency.size())
            throw std::invalid_argument("k must be between zero and the unique value count");
        std::vector<int> answer;
        answer.reserve(static_cast<std::size_t>(k));
        if (k == 0) return answer;
        std::vector<std::vector<int>> buckets(nums.size() + 1);
        for (const auto& entry : frequency) buckets[entry.second].push_back(entry.first);
        for (std::size_t count = buckets.size() - 1; count > 0; --count) {
            for (int value : buckets[count]) {
                answer.push_back(value);
                if (answer.size() == static_cast<std::size_t>(k)) return answer;
            }
        }
        return answer;
    }
};
}  // namespace lab
