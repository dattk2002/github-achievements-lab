#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace lab {

// Precondition: values is sorted in ascending order.
inline std::optional<std::pair<std::size_t, std::size_t>> two_sum_sorted(
    const std::vector<int>& values, long long target) {
    if (values.size() < 2) return std::nullopt;
    std::size_t left = 0;
    std::size_t right = values.size() - 1;
    while (left < right) {
        const long long sum = static_cast<long long>(values[left]) + values[right];
        if (sum == target) return std::make_pair(left, right);
        if (sum < target) ++left;
        else --right;
    }
    return std::nullopt;
}

}  // namespace lab
