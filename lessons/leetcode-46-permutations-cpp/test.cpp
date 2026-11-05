#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <set>
void verify(std::vector<int> nums) {
    const auto before=nums;
    auto ordered=nums; std::sort(ordered.begin(),ordered.end());
    std::set<std::vector<int>> expected;
    do { expected.insert(ordered); } while (std::next_permutation(ordered.begin(),ordered.end()));
    lab::Solution solution;
    const auto output=solution.permute(nums);
    const std::set<std::vector<int>> actual(output.begin(),output.end());
    check(actual==expected,"permutation set");
    check(actual.size()==output.size(),"duplicate permutations");
    check(nums==before,"input mutated");
}
int main() {
    verify({2,-3,5}); verify({}); verify({-10}); verify({-10,10});
    const int alphabet[]{-3,-1,0,2,5,8};
    for (unsigned mask=0; mask<64; ++mask) {
        std::vector<int> nums;
        for (unsigned i=0; i<6; ++i) if ((mask>>i)&1U) nums.push_back(alphabet[i]);
        std::reverse(nums.begin(),nums.end()); verify(nums);
    }
    std::cout << "Permutations: passed\n";
}
