#pragma once
#include <vector>

namespace lab {
class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        int entry = 0;
        while (entry != slow) {
            entry = nums[entry];
            slow = nums[slow];
        }
        return entry;
    }
};
}  // namespace lab
