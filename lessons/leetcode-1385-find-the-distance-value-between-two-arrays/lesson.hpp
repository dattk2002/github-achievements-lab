#pragma once

#include <cstdlib>
#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: lengths 1..500, values -1000..1000, d in 0..100.
    // Neither input is modified.
    int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2,
                             int d) {
        int count = 0;
        for (int x : arr1) {
            bool qualifies = true;
            for (int y : arr2) {
                if (std::abs(x - y) <= d) {
                    qualifies = false;
                    break;
                }
            }
            if (qualifies) ++count;
        }
        return count;
    }
};
}  // namespace lab
