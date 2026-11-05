#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
void verify(std::vector<int> nums,int target) {
    const auto before=nums;
    const auto position=std::find(nums.begin(),nums.end(),target);
    const int expected=position==nums.end() ? -1 : static_cast<int>(position-nums.begin());
    lab::Solution solution;
    check(solution.search(nums,target)==expected,"rotated search index");
    check(nums==before,"input mutated");
}
int main() {
    verify({8,11,14,-5,-1,3},-1); verify({8,11,14,-5,-1,3},0);
    verify({},4); verify({2},2); verify({2},1); verify({2,1},1); verify({1,2},2);
    for (int n=1; n<=60; ++n) {
        std::vector<int> sorted;
        for (int i=0; i<n; ++i) sorted.push_back(3*i-100);
        for (int offset=0; offset<n; ++offset) {
            auto nums=sorted; std::rotate(nums.begin(),nums.begin()+offset,nums.end());
            for (int target=-101; target<=3*(n-1)-99; ++target) verify(nums,target);
        }
    }
    std::vector<int> large;
    for (int i=0; i<5000; ++i) large.push_back(-10000+4*i);
    std::rotate(large.begin(),large.begin()+2501,large.end());
    for (int target:{-10000,-9996,0,9996,10000,-9999}) verify(large,target);
    std::cout << "Rotated search: passed\n";
}
