#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace lab {

// Preconditions: all prefix sums and queried range sums fit in long long.
class PrefixSums {
public:
    explicit PrefixSums(const std::vector<int>& values) {
        for (int value : values) prefix_.push_back(prefix_.back() + value);
    }

    long long range_sum(std::size_t begin, std::size_t end) const {
        if (begin > end || end >= prefix_.size()) {
            throw std::out_of_range("range_sum requires 0 <= begin <= end <= size");
        }
        return prefix_[end] - prefix_[begin];
    }

private:
    std::vector<long long> prefix_{0};
};

}  // namespace lab
