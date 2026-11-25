#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

namespace lab {
namespace {

int bruteForce(const std::vector<int>& nums) {
    for (auto width = 1; width <= nums.end() - nums.begin(); ++width) {
        std::map<std::vector<int>, int> counts;
        for (auto start = nums.begin(); start <= nums.end() - width; ++start) {
            ++counts[std::vector<int>(start, start + width)];
        }
        for (const auto& entry : counts) {
            if (entry.second == 1) {
                return static_cast<int>(width);
            }
        }
    }
    return 0;
}

void check(Solution& solution, const char* name, std::vector<int> nums, int expected) {
    const auto original = nums;
    const int actual = solution.smallestUniqueSubarray(nums);
    if (actual != expected || nums != original) {
        std::cerr << name << " (n=" << original.size() << "): expected " << expected
                  << ", got " << actual << ", input changed: " << (nums != original) << '\n';
        std::exit(EXIT_FAILURE);
    }
}

void runTests() {
    Solution solution;
    check(solution, "one element at the maximum value", {100000}, 1);
    check(solution, "one singleton value", {8, 4, 8, 9, 4}, 1);
    check(solution, "only the whole constant array is unique", {6, 6, 6, 6, 6}, 5);
    check(solution, "the middle pair is unique", {4, 9, 4, 9}, 2);
    check(solution, "the middle triple is unique", {4, 9, 4, 9, 4}, 3);

    int casesAtLength = 1;
    int comparisons = 0;
    const int values[] = {1, 37, 100000};
    for (int length = 1; length <= 8; ++length) {
        casesAtLength *= 3;
        for (int code = 0; code < casesAtLength; ++code) {
            std::vector<int> nums(length);
            int digits = code;
            for (int& value : nums) {
                value = values[digits % 3];
                digits /= 3;
            }
            check(solution, "exhaustive oracle comparison", nums, bruteForce(nums));
            ++comparisons;
        }
    }

    check(solution, "maximum length, constant", std::vector<int>(100000, 100000), 100000);
    // With three windows, the middle start is the only one of its parity.
    // With four or more windows, both start parities occur at least twice.
    std::vector<int> alternating(100000, 1);
    for (std::size_t i = 1; i < alternating.size(); i += 2) {
        alternating[i] = 100000;
    }
    check(solution, "maximum length, alternating", alternating, 99998);
    std::cout << "Smallest unique subarray: " << comparisons
              << " exhaustive comparisons and boundary cases passed\n";
}

}  // namespace
}  // namespace lab

int main() {
    lab::runTests();
}
