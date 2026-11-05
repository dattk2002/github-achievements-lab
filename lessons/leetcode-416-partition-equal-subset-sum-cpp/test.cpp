#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <numeric>
bool oracle(const std::vector<int>& nums) {
    if (nums.empty()) return false;
    const int total=std::accumulate(nums.begin(),nums.end(),0);
    for (unsigned mask=0; mask<(1U<<nums.size()); ++mask) {
        int selected=0;
        for (std::size_t i=0; i<nums.size(); ++i) if ((mask>>i)&1U) selected+=nums[i];
        if (selected*2==total) return true;
    }
    return false;
}
void verify(std::vector<int> nums,bool expected) {
    const auto before=nums; lab::Solution solution;
    check(solution.canPartition(nums)==expected,"equal partition feasibility");
    check(nums==before,"input mutated");
}
int main() {
    verify({2,4,6},true); verify({},false); verify({2},false); verify({3,3},true);
    verify({1,2,5},false); verify({2,3,7},false); verify({1,2},false);
    verify({4,4,6,6},true); verify({1,1,3,5},true);
    unsigned count=1; const int alphabet[]{1,2,4};
    for (unsigned length=1; length<=7; ++length) {
        count*=3;
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::vector<int> nums;
            for (unsigned i=0; i<length; ++i) { nums.push_back(alphabet[value%3]); value/=3; }
            verify(nums,oracle(nums));
        }
    }
    verify(std::vector<int>(200,100),true); verify(std::vector<int>(199,100),false);
    verify(std::vector<int>(200,1),true);
    std::cout << "Equal partition: passed\n";
}
