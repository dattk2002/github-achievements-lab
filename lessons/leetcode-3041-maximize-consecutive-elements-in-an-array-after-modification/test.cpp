#include "lesson.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

namespace lab {
namespace {

bool check(const char* name, std::vector<int> nums, int expected) {
    const int actual = Solution{}.maxSelectedElements(nums);
    if (actual == expected) return true;

    std::cerr << name << ": expected " << expected << ", got " << actual
              << " (input:";
    const auto sampleSize = std::min<std::size_t>(nums.size(), 12);
    for (std::size_t i = 0; i < sampleSize; ++i) std::cerr << ' ' << nums[i];
    if (sampleSize < nums.size()) std::cerr << " ...";
    std::cerr << ")\n";
    return false;
}

int exhaustiveAnswer(const std::vector<int>& nums) {
    int best = 0;
    for (unsigned mask = 0; mask < (1u << nums.size()); ++mask) {
        auto adjusted = nums;
        for (std::size_t i = 0; i < nums.size(); ++i) {
            adjusted[i] += (mask >> i) & 1u;
        }
        std::sort(adjusted.begin(), adjusted.end());
        adjusted.erase(std::unique(adjusted.begin(), adjusted.end()), adjusted.end());

        int run = 1;
        for (std::size_t i = 1; i < adjusted.size(); ++i) {
            run = adjusted[i] == adjusted[i - 1] + 1 ? run + 1 : 1;
            best = std::max(best, run);
        }
        best = std::max(best, run);
    }
    return best;
}

bool checkSmallInputs(std::vector<int>& nums, int remaining) {
    if (remaining == 0) {
        return check("exhaustive increments", nums, exhaustiveAnswer(nums));
    }
    for (int value = 1; value <= 4; ++value) {
        nums.push_back(value);
        const bool passed = checkSmallInputs(nums, remaining - 1);
        nums.pop_back();
        if (!passed) return false;
    }
    return true;
}

bool runTests() {
    bool passed = true;
    passed &= check("one element cannot be reused", {1}, 1);
    passed &= check("equal elements offer two distinct values", {6, 6, 6, 6}, 2);
    passed &= check("increments bridge gaps", {9, 5, 7, 7}, 4);
    passed &= check("large gaps break the run", {3, 8, 14}, 1);
    passed &= check("upper bound can be incremented", {1000000, 999999, 1000000}, 3);

    std::vector<int> large(100000);
    for (int i = 0; i < 100000; ++i) large[i] = 100000 - i;
    passed &= check("maximum length in reverse order", large, 100000);

    std::vector<int> small;
    for (int size = 1; size <= 5; ++size) {
        if (!checkSmallInputs(small, size)) return false;
    }
    return passed;
}

}  // namespace
}  // namespace lab

int main() {
    return lab::runTests() ? 0 : 1;
}
