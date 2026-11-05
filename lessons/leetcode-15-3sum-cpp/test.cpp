#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <set>
using Triples=std::set<std::vector<int>>;
Triples oracle(const std::vector<int>& nums) {
    Triples result;
    for (std::size_t i=0; i<nums.size(); ++i)
        for (std::size_t j=i+1; j<nums.size(); ++j)
            for (std::size_t k=j+1; k<nums.size(); ++k)
                if (nums[i]+nums[j]+nums[k]==0) {
                    std::vector<int> triple{nums[i],nums[j],nums[k]};
                    std::sort(triple.begin(),triple.end()); result.insert(triple);
                }
    return result;
}
void verify(std::vector<int> nums, const Triples& expected) {
    const auto before=nums; lab::Solution solution;
    auto output=solution.threeSum(nums);
    for (auto& triple:output) {
        check(triple.size()==3,"triplet size");
        std::sort(triple.begin(),triple.end());
    }
    const Triples actual(output.begin(),output.end());
    check(actual==expected,"3Sum values or missing result");
    check(actual.size()==output.size(),"duplicate output triplets");
    check(nums==before,"input mutated");
}
int main() {
    verify({-4,-1,0,1,2,3},{{-4,1,3},{-1,0,1}});
    verify({},{}); verify({0,0},{}); verify({0,0,0,0},{{0,0,0}});
    verify({-2,1},{}); verify({-2,1,1},{{-2,1,1}}); verify({1,2,3},{});
    const std::vector<int> extremes{-100000,50000,50000,100000,-50000,-50000,0};
    verify(extremes,oracle(extremes));
    unsigned count=1; const int alphabet[]{-2,-1,0,1,2};
    for (unsigned length=0; length<=6; ++length) {
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::vector<int> nums;
            for (unsigned i=0; i<length; ++i) { nums.push_back(alphabet[value%5]); value/=5; }
            verify(nums,oracle(nums));
        }
        count*=5;
    }
    verify(std::vector<int>(3000,0),{{0,0,0}});
    std::cout << "3Sum: passed\n";
}
