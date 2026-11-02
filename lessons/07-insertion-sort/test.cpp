#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <algorithm>
void verify(std::vector<int> input) {
    auto expected=input;
    std::sort(expected.begin(),expected.end());
    lab::insertion_sort(input);
    check(input==expected, "insertion sort differs from std::sort");
}
int main() {
    verify({2,1}); verify({}); verify({4}); verify({1,2,3,4});
    verify({9,7,5,3,1}); verify({4,4,4}); verify({-2,3,-2,0,-8});
    verify({std::numeric_limits<int>::max(),0,std::numeric_limits<int>::min(),-1});
    unsigned count=1;
    for (unsigned length=0; length<=7; ++length) {
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code;
            std::vector<int> input;
            for (unsigned i=0; i<length; ++i) { input.push_back(static_cast<int>(value%3)-1); value/=3; }
            verify(input);
        }
        count*=3;
    }
    unsigned state=7;
    for (unsigned length=0; length<160; ++length) {
        std::vector<int> input;
        for (unsigned i=0; i<length; ++i) { state=state*1664525U+1013904223U; input.push_back(static_cast<int>(state%2001)-1000); }
        verify(input);
    }
    std::cout << "Insertion sort: passed\n";
}
