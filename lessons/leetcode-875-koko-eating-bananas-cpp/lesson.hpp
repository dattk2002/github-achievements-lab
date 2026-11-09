#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace lab {
class Solution {
public:
    int minEatingSpeed(std::vector<int>& piles, int h) {
        if (piles.empty() || static_cast<long long>(h) < static_cast<long long>(piles.size()))
            throw std::invalid_argument("nonempty piles and at least one hour per pile required");
        int low = 1;
        int high = *std::max_element(piles.begin(), piles.end());
        while (low < high) {
            const int speed = low + (high - low) / 2;
            long long hours = 0;
            for (int pile : piles)
                hours += (static_cast<long long>(pile) + speed - 1) / speed;
            if (hours <= h) high = speed;
            else low = speed + 1;
        }
        return low;
    }
};
}  // namespace lab
