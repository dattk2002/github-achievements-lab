#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

namespace lab {
namespace {
// Enumerate actual sums, independently of prefix-parity counting.
int oracle(const std::vector<int>& arr) {
    int answer = 0;
    for (std::size_t left = 0; left < arr.size(); ++left) {
        int sum = 0;
        for (std::size_t right = left; right < arr.size(); ++right) {
            sum += arr[right];
            if (sum % 2 != 0) ++answer;
        }
    }
    return answer;
}

void check(Solution& solution, std::vector<int> arr, int expected) {
    const auto before = arr;
    const int actual = solution.numOfSubarrays(arr);
    if (actual != expected || arr != before) {
        std::cerr << "n=" << arr.size() << ": expected " << expected
                  << ", got " << actual << "; input must remain unchanged\n";
        std::exit(EXIT_FAILURE);
    }
}
}  // namespace

void run_tests() {
    Solution solution; // Reuse the instance to catch leaked state.
    check(solution, {1}, 1);
    check(solution, {100}, 0);
    check(solution, {99}, 1);
    check(solution, {8, 3, 6}, 4);
    check(solution, {3, 7}, 2);
    check(solution, {2, 6, 8, 100}, 0);
    check(solution, {3, 3, 3, 3}, 6);
    check(solution, {1, 100, 100, 1}, 6);

    int comparisons = 0;
    const int values[] = {1, 2, 99, 100};
    for (int n = 1; n <= 7; ++n) {
        int count = 1;
        for (int i = 0; i < n; ++i) count *= 4;
        for (int code = 0; code < count; ++code) {
            int digits = code;
            std::vector<int> arr(n);
            for (int& value : arr) {
                value = values[digits % 4];
                digits /= 4;
            }
            check(solution, arr, oracle(arr));
            ++comparisons;
        }
    }

    check(solution, std::vector<int>(100000, 100), 0);
    // All odd: sum over odd lengths = 50000 * 50001 = 2500050000.
    check(solution, std::vector<int>(100000, 99), 500049986);
    // One odd at index 49999: 50000 left choices * 50001 right choices.
    std::vector<int> middle(100000, 100);
    middle[49999] = 1;
    check(solution, middle, 500049986);
    middle[49999] = 100;
    middle.front() = 1;
    check(solution, middle, 100000);
    std::cout << "odd-sum subarrays: boundaries and " << comparisons
              << " exhaustive comparisons passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
