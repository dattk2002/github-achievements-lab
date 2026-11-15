#pragma once

#include <vector>

namespace lab {
class Solution {
public:
    // Preconditions: 1 <= arr.size() <= 100000, 1 <= arr[i] <= 100.
    // Preserves arr; returns the count modulo 1000000007.
    int numOfSubarrays(std::vector<int>& arr) {
        constexpr long long mod = 1000000007LL;
        long long counts[2] = {1, 0}; // Include the empty, even prefix.
        long long answer = 0;
        int parity = 0;
        for (int value : arr) {
            parity ^= value % 2;
            answer = (answer + counts[1 - parity]) % mod;
            ++counts[parity];
        }
        return static_cast<int>(answer);
    }
};
}  // namespace lab
