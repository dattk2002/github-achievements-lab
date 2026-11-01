#include "lesson.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

void expect(const std::vector<int>& values, long long target, bool exists) {
    const auto before = values;
    const auto answer = lab::two_sum_sorted(values, target);
    check(values == before, "input was mutated");
    check(answer.has_value() == exists, "wrong pair existence");
    if (answer) {
        const auto [left, right] = *answer;
        check(left < right && right < values.size(), "invalid or reused indices");
        check(static_cast<long long>(values[left]) + values[right] == target, "wrong pair sum");
    }
}

int main() {
    expect({}, 0, false);
    expect({4}, 8, false);
    expect({4, 4}, 8, true);
    expect({-8, -3, 1, 6, 9}, -11, true);
    expect({-8, -3, 1, 6, 9}, 15, true);
    expect({-8, -3, 1, 6, 9}, -2, true);
    expect({-8, -3, 1, 6, 9}, 4, false);
    expect({0, 0, 0}, 0, true);
    const int low = std::numeric_limits<int>::min();
    const int high = std::numeric_limits<int>::max();
    expect({low, low, 0, high, high}, 2LL * low, true);
    expect({low, low, 0, high, high}, 2LL * high, true);
    expect({low, high}, -1, true);
    expect({low, high}, std::numeric_limits<long long>::min(), false);
    expect({low, high}, std::numeric_limits<long long>::max(), false);
    // A quadratic oracle deliberately avoids the two-pointer argument.
    for (int length = 0, combinations = 1; length <= 6; ++length, combinations *= 4) {
        for (int code = 0; code < combinations; ++code) {
            std::vector<int> values;
            int digits = code;
            for (int i = 0; i < length; ++i, digits /= 4) values.push_back(digits % 4 - 2);
            std::sort(values.begin(), values.end());
            for (long long target = -5; target <= 3; ++target) {
                bool exists = false;
                for (std::size_t i = 0; i < values.size(); ++i)
                    for (std::size_t j = i + 1; j < values.size(); ++j)
                        if (static_cast<long long>(values[i]) + values[j] == target) exists = true;
                expect(values, target, exists);
            }
        }
    }
    std::cout << "two sum sorted: all cases passed\n";
}
