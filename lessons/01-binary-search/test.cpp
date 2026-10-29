#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

void expect(const std::vector<int>& values, int target,
            std::optional<std::size_t> wanted) {
    if (lab::binary_search_first(values, target) != wanted) {
        std::cerr << "binary_search_first failed for target " << target << '\n';
        std::exit(EXIT_FAILURE);
    }
}

int main() {
    expect({}, 7, std::nullopt);
    expect({7}, 7, 0);
    expect({7}, 6, std::nullopt);
    expect({-5, -1, 0, 3, 9}, -5, 0);
    expect({-5, -1, 0, 3, 9}, 9, 4);
    expect({-5, -1, 0, 3, 9}, 2, std::nullopt);
    expect({1, 2, 2, 2, 8}, 2, 1);
    expect({2, 2, 2}, 2, 0);
    expect({std::numeric_limits<int>::min(), 0,
            std::numeric_limits<int>::max()},
           std::numeric_limits<int>::max(), 2);

    // Compare against a standard-library oracle for every sorted vector
    // of length <= 6 with values in {-1, 0, 1}.
    for (int length = 0; length <= 6; ++length) {
        int combinations = 1;
        for (int i = 0; i < length; ++i) combinations *= 3;
        for (int code = 0; code < combinations; ++code) {
            std::vector<int> values;
            int digits = code;
            for (int i = 0; i < length; ++i) {
                values.push_back(digits % 3 - 1);
                digits /= 3;
            }
            std::sort(values.begin(), values.end());
            for (int target = -2; target <= 2; ++target) {
                const auto found = std::find(values.begin(), values.end(), target);
                const auto wanted = found == values.end()
                    ? std::nullopt
                    : std::optional<std::size_t>(found - values.begin());
                expect(values, target, wanted);
            }
        }
    }
    std::cout << "binary search: all cases passed\n";
}
