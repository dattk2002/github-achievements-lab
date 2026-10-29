#pragma once

#include <cstddef>
#include <optional>
#include <vector>

namespace lab {

// Precondition: values is sorted in ascending order.
inline std::optional<std::size_t> binary_search_first(
    const std::vector<int>& values, int target) {
    std::size_t left = 0;
    std::size_t right = values.size();
    while (left < right) {
        const auto middle = left + (right - left) / 2;
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    if (left < values.size() && values[left] == target) return left;
    return std::nullopt;
}

}  // namespace lab
