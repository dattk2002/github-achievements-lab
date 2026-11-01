#pragma once

#include <cstddef>
#include <optional>
#include <vector>

namespace lab {

struct SearchResult {
    std::optional<std::size_t> index;
    std::size_t comparisons;
};

inline SearchResult linear_search(const std::vector<int>& values, int target) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (values[i] == target) return {i, i + 1};
    }
    return {std::nullopt, values.size()};
}

}  // namespace lab
