#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

void expect(const std::vector<int>& values, int target,
            std::optional<std::size_t> index, std::size_t comparisons) {
    const auto before = values;
    const auto result = lab::linear_search(values, target);
    if (result.index != index || result.comparisons != comparisons || values != before) {
        std::cerr << "linear search: wrong index, comparison count or input mutation\n";
        std::exit(EXIT_FAILURE);
    }
}

int main() {
    expect({}, 8, std::nullopt, 0);
    expect({8}, 8, 0, 1);
    expect({8}, 3, std::nullopt, 1);
    expect({9, -2, 9, 0}, 9, 0, 1);
    expect({9, -2, 9, 0}, -2, 1, 2);
    expect({9, -2, 9, 0}, 0, 3, 4);
    expect({9, -2, 9, 0}, 7, std::nullopt, 4);
    expect({std::numeric_limits<int>::max(), 0, std::numeric_limits<int>::min()},
           std::numeric_limits<int>::min(), 2, 3);
    // std::find supplies an independent index oracle on unsorted vectors.
    for (int length = 0, combinations = 1; length <= 7; ++length, combinations *= 3) {
        for (int code = 0; code < combinations; ++code) {
            std::vector<int> values;
            int digits = code;
            for (int i = 0; i < length; ++i, digits /= 3) values.push_back(digits % 3 - 1);
            for (int target = -2; target <= 2; ++target) {
                const auto found = std::find(values.begin(), values.end(), target);
                const auto index = found == values.end() ? std::nullopt
                    : std::optional<std::size_t>(found - values.begin());
                expect(values, target, index, index ? *index + 1 : values.size());
            }
        }
    }
    std::cout << "linear search: all cases passed\n";
}
