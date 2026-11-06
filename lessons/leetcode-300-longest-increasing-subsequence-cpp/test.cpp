#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
int oracle(const std::vector<int>& nums) {
    std::vector<int> ending(nums.size(),1); int best=0;
    for (std::size_t i=0; i<nums.size(); ++i) {
        for (std::size_t j=0; j<i; ++j) if (nums[j]<nums[i]) ending[i]=std::max(ending[i],ending[j]+1);
        best=std::max(best,ending[i]);
    }
    return best;
}
void verify(std::vector<int> nums,int expected) {
    const auto before=nums; lab::Solution solution;
    check(solution.lengthOfLIS(nums)==expected,"strict LIS length");
    check(nums==before,"input mutated");
}
int main() {
    verify({4,1,5,2,6,3},3); verify({},0); verify({8},1); verify({2,2,2},1);
    verify({-10000,0,10000},3); verify({5,4,3,2,1},1); verify({1,2,2,3},3);
    unsigned count=1; const int alphabet[]{-2,-1,0,1,2};
    for (unsigned length=0; length<=6; ++length) {
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::vector<int> nums;
            for (unsigned i=0; i<length; ++i) { nums.push_back(alphabet[value%5]); value/=5; }
            verify(nums,oracle(nums));
        }
        count*=5;
    }
    std::vector<int> increasing; for (int i=0; i<2500; ++i) increasing.push_back(i);
    verify(increasing,2500); std::reverse(increasing.begin(),increasing.end());verify(increasing,1);
    verify(std::vector<int>(2500,7),1);
    std::cout << "LIS: passed\n";
}
