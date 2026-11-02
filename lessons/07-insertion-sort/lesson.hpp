#pragma once

#include <cstddef>
#include <vector>

namespace lab {

inline void insertion_sort(std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        const int key = values[i];
        std::size_t position = i;
        while (position > 0 && values[position - 1] > key) {
            values[position] = values[position - 1];
            --position;
        }
        values[position] = key;
    }
}

}  // namespace lab
