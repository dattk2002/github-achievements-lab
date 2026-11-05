#pragma once

#include <unordered_map>
#include <vector>

namespace lab {
class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::unordered_map<long long, int> frequency;
        frequency.reserve(nums.size() + 1);
        frequency[0] = 1;
        long long prefix = 0;
        int count = 0;
        for (int value : nums) {
            prefix += value;
            const auto match = frequency.find(prefix - k);
            if (match != frequency.end()) {
                count += match->second;
            }
            ++frequency[prefix];
        }
        return count;
    }
};
}  // namespace lab
