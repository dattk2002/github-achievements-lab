#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

namespace lab {
namespace {
void check(const char* name, std::vector<int> arr1, std::vector<int> arr2,
           int d, int expected) {
    const auto before1 = arr1;
    const auto before2 = arr2;
    Solution solution;
    const int actual = solution.findTheDistanceValue(arr1, arr2, d);
    if (actual != expected || arr1 != before1 || arr2 != before2) {
        std::cerr << name << ": expected " << expected << ", got " << actual
                  << "; inputs must stay unchanged\n";
        std::exit(EXIT_FAILURE);
    }
}
}  // namespace

void run_tests() {
    check("mixed distances", {-6, 0, 5, 12}, {-4, 8}, 2, 3);
    check("exact lower boundary", {3}, {5}, 2, 0);
    check("exact upper boundary", {7}, {5}, 2, 0);
    check("one beyond threshold", {2, 8}, {5}, 2, 2);
    check("zero threshold and duplicates", {2, 2, 3, -1}, {2, 2, -1}, 0, 1);
    check("count occurrences", {4, 4, 4}, {-2}, 1, 3);
    check("single equal", {-1000}, {-1000}, 0, 0);
    check("opposite extremes", {-1000, 1000}, {0}, 100, 2);
    check("maximum threshold", {-1000, -900, -899, 1000}, {-1000}, 100, 2);
    check("negative values", {-9, -5, -1}, {-7}, 1, 3);
    check("late disqualifier", {6}, {-1000, 1000, -8, 7}, 1, 0);
    check("early disqualifier", {6}, {7, -1000, 1000}, 1, 0);
    check("all excluded", {-3, 0, 3}, {-2, 1, 4}, 1, 0);
    check("maximum sizes all counted", std::vector<int>(500, -1000),
          std::vector<int>(500, 1000), 100, 500);
    auto late_match = std::vector<int>(500, 1000);
    late_match.back() = -900;
    check("maximum sizes last match", std::vector<int>(500, -1000),
          late_match, 100, 0);
    std::cout << "distance value: 15 cases passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
