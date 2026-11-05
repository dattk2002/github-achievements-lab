#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
int oracle(const std::vector<int>& nums,int k) {
    int count=0;
    for (std::size_t begin=0; begin<nums.size(); ++begin) {
        int sum=0;
        for (std::size_t end=begin; end<nums.size(); ++end) { sum+=nums[end]; if (sum==k) ++count; }
    }
    return count;
}
void verify(std::vector<int> nums,int k,int expected) {
    const auto before=nums; lab::Solution solution;
    check(solution.subarraySum(nums,k)==expected,"subarray count");
    check(nums==before,"input mutated");
}
int main() {
    verify({2,-2,2,-2},0,4); verify({3,-1,-2,3},3,3);
    verify({},0,0); verify({0},0,1); verify({7},7,1); verify({7},0,0);
    unsigned count=1; const int alphabet[]{-2,-1,0,1,2};
    for (unsigned length=0; length<=6; ++length) {
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::vector<int> nums;
            for (unsigned i=0; i<length; ++i) { nums.push_back(alphabet[value%5]); value/=5; }
            for (int k=-4; k<=4; ++k) verify(nums,k,oracle(nums,k));
        }
        count*=5;
    }
    verify(std::vector<int>(20000,0),0,200010000);
    verify(std::vector<int>(20000,1000),10000000,10001);
    verify(std::vector<int>(20000,-1000),-10000000,10001);
    std::cout << "Subarray sum count: passed\n";
}
