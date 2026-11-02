#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {

// Both inputs must already be sorted in nondecreasing order.
inline std::vector<int> merge_sorted(const std::vector<int>& first,
                                     const std::vector<int>& second) {
    std::vector<int> result;
    if (first.size() > result.max_size() ||
        second.size() > result.max_size() - first.size()) {
        throw std::length_error("Merged sequence exceeds max_size");
    }
    result.reserve(first.size() + second.size());
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < first.size() && j < second.size()) {
        if (first[i] <= second[j]) {
            result.push_back(first[i++]);
        } else {
            result.push_back(second[j++]);
        }
    }
    while (i < first.size()) {
        result.push_back(first[i++]);
    }
    while (j < second.size()) {
        result.push_back(second[j++]);
    }
    return result;
}

}  // namespace lab
