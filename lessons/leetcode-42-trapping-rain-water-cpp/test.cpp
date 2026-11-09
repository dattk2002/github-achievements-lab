#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

int oracle(const std::vector<int>& a) {
    int water = 0;
    for (std::size_t i=0; i<a.size(); ++i) {
        int left=0, right=0;
        for (std::size_t j=0; j<=i; ++j) if (a[j]>left) left=a[j];
        for (std::size_t j=i; j<a.size(); ++j) if (a[j]>right) right=a[j];
        water += (left<right ? left : right)-a[i];
    }
    return water;
}
void check(std::vector<int> a, int expected) {
    const auto original=a;
    require(lab::Solution{}.trap(a)==expected,"rain-water volume differs");
    require(a==original,"height input changed");
}
void enumerate(std::vector<int>& a,int remaining) {
    if (remaining==0) { check(a,oracle(a)); return; }
    for (int h : {0,1,3,5}) { a.push_back(h); enumerate(a,remaining-1); a.pop_back(); }
}
int main() {
    check({4,1,2,0,3},6); check({5,0,0,5},10);
    check({3,2,1},0); check({1,2,3},0); check({},0); check({8},0);
    check({2,0,2,0,2},4);
    std::vector<int> a;
    for (int n=0;n<=6;++n) enumerate(a,n);
    a.assign(20000,0); a.front()=100000; a.back()=100000;
    check(a,1999800000); check(std::vector<int>(20000,100000),0);
    std::cout << "LC42: fixed, 5461 oracle and limit cases passed\n";
}
