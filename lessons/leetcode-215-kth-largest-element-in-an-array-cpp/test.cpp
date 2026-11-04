#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <functional>
#include <stdexcept>
void verify(std::vector<int> values, int k, int expected) {
    const auto before=values;
    lab::Solution solution;
    check(solution.findKthLargest(values,k)==expected,"kth largest value including duplicates");
    check(values==before,"input mutated");
}
int main() {
    verify({7,7,3,-2,9},3,7); verify({-4},1,-4);
    verify({-10000,10000,0},1,10000); verify({-10000,10000,0},3,-10000);
    verify({-9,-2,-9,-4},2,-4);
    unsigned count=1; const int alphabet[]{-2,0,5};
    for (unsigned length=1; length<=6; ++length) {
        count*=3;
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::vector<int> values;
            for (unsigned i=0; i<length; ++i) { values.push_back(alphabet[value%3]); value/=3; }
            auto sorted=values; std::sort(sorted.begin(),sorted.end(),std::greater<int>{});
            for (unsigned k=1; k<=length; ++k) verify(values,static_cast<int>(k),sorted[k-1]);
        }
    }
    std::vector<int> large(100000,7); large[123]=10000;
    verify(large,1,10000); verify(large,50000,7); verify(large,100000,7);
    for (int k : {-1,0,4}) {
        std::vector<int> values{1,2,3}; lab::Solution solution; bool caught=false;
        try { (void)solution.findKthLargest(values,k); } catch (const std::out_of_range&) { caught=true; }
        check(caught,"invalid rank rejected");
    }
    std::vector<int> empty; lab::Solution solution; bool caught=false;
    try { (void)solution.findKthLargest(empty,1); } catch (const std::out_of_range&) { caught=true; }
    check(caught,"empty sequence rejected");
    std::cout << "Kth largest: passed\n";
}
