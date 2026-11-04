#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <stdexcept>
int oracle(const std::vector<int>& values) {
    int best=values.front();
    for (std::size_t begin=0; begin<values.size(); ++begin) {
        int sum=0;
        for (std::size_t end=begin; end<values.size(); ++end) { sum+=values[end]; best=std::max(best,sum); }
    }
    return best;
}
void verify(std::vector<int> values, int expected) {
    const auto before=values;
    lab::Solution solution;
    check(solution.maxSubArray(values)==expected,"maximum subarray sum");
    check(values==before,"input mutated");
}
int main() {
    verify({-8,-2,-5},-2); verify({-7},-7); verify({9},9); verify({0,0},0);
    verify({-6,3,5,-2,4,-9,7},10); verify({5,-20,8,2},10);
    verify({10000,-1,10000},19999);
    unsigned count=1;
    const int alphabet[]{-3,-1,0,2,4};
    for (unsigned length=1; length<=6; ++length) {
        count*=5;
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::vector<int> values;
            for (unsigned i=0; i<length; ++i) { values.push_back(alphabet[value%5]); value/=5; }
            verify(values,oracle(values));
        }
    }
    verify(std::vector<int>(100000,10000),1000000000);
    verify(std::vector<int>(100000,-10000),-10000);
    bool rejected=false; std::vector<int> empty; lab::Solution solution;
    try { (void)solution.maxSubArray(empty); } catch (const std::invalid_argument&) { rejected=true; }
    check(rejected,"empty input must be rejected");
    std::cout << "Maximum subarray: passed\n";
}
