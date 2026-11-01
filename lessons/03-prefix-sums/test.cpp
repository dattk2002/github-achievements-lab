#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>

void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

void invalid(const lab::PrefixSums& sums, std::size_t begin, std::size_t end) {
    try { (void)sums.range_sum(begin, end); }
    catch (const std::out_of_range&) { return; }
    catch (...) { check(false, "wrong exception type"); }
    check(false, "invalid range accepted");
}

int main() {
    std::vector<int> input{7, -3, 9, -1};
    const lab::PrefixSums sums(input);
    check(sums.range_sum(0, 4) == 12, "whole range");
    check(sums.range_sum(1, 3) == 6, "half-open interior");
    check(sums.range_sum(2, 3) == 9, "singleton");
    check(sums.range_sum(0, 0) == 0 && sums.range_sum(4, 4) == 0, "empty endpoints");
    check(input == std::vector<int>({7, -3, 9, -1}), "constructor mutated input");
    input[0] = 99;
    check(sums.range_sum(0, 1) == 7, "prefix sums must own a snapshot");
    const lab::PrefixSums empty({});
    check(empty.range_sum(0, 0) == 0, "empty input");
    invalid(empty, 0, 1);
    invalid(empty, 1, 1);
    invalid(sums, 3, 2);
    invalid(sums, 0, 5);
    invalid(sums, 5, 5);
    invalid(sums, std::numeric_limits<std::size_t>::max(), 0);
    invalid(sums, 0, std::numeric_limits<std::size_t>::max());
    const int high = std::numeric_limits<int>::max();
    const int low = std::numeric_limits<int>::min();
    const lab::PrefixSums extremes({high, high, low, low});
    check(extremes.range_sum(0, 2) == 2LL * high, "positive sum exceeds int");
    check(extremes.range_sum(2, 4) == 2LL * low, "negative sum exceeds int");
    check(extremes.range_sum(0, 4) == -2, "cancellation across extremes");
    for (int length = 0, combinations = 1; length <= 6; ++length, combinations *= 3) {
        for (int code = 0; code < combinations; ++code) {
            std::vector<int> values;
            int digits = code;
            for (int i = 0; i < length; ++i, digits /= 3) values.push_back(2 * (digits % 3 - 1));
            const lab::PrefixSums prefix(values);
            for (std::size_t begin = 0; begin <= values.size(); ++begin) {
                for (std::size_t end = begin; end <= values.size(); ++end) {
                    const long long wanted = std::accumulate(values.begin() + begin,
                                                            values.begin() + end, 0LL);
                    check(prefix.range_sum(begin, end) == wanted, "direct-sum oracle mismatch");
                }
            }
        }
    }
    std::cout << "prefix sums: all cases passed\n";
}
