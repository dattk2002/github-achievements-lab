#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

std::vector<int> oracle(const std::vector<int>& a,int k) {
    std::vector<int> result;
    for (std::size_t left=0;left+static_cast<std::size_t>(k)<=a.size();++left) {
        int best=a[left];
        for (int j=1;j<k;++j) if (a[left+j]>best) best=a[left+j];
        result.push_back(best);
    }
    return result;
}
void check(std::vector<int> a,int k,const std::vector<int>& expected) {
    const auto original=a;
    require(lab::Solution{}.maxSlidingWindow(a,k)==expected,"sliding maximum differs");
    require(a==original,"sliding-window input changed");
}
void enumerate(std::vector<int>& a,int remaining) {
    if (remaining==0) {
        for (int k=1;k<=static_cast<int>(a.size());++k) check(a,k,oracle(a,k));
        return;
    }
    for (int x : {-2,0,2}) { a.push_back(x); enumerate(a,remaining-1); a.pop_back(); }
}
void invalid(std::vector<int> a,int k) {
    const auto original=a; bool threw=false;
    try { (void)lab::Solution{}.maxSlidingWindow(a,k); }
    catch (const std::invalid_argument&) { threw=true; }
    require(threw,"invalid window must throw"); require(a==original,"invalid input changed");
}
int main() {
    check({4,1,7,3,8,2},3,{7,7,8,8});
    check({5,5,1,5},2,{5,5,5}); check({-4,-2,-5},2,{-2,-2});
    check({3,2,1},1,{3,2,1}); check({3,2,1},3,{3});
    std::vector<int> a;
    for (int n=1;n<=7;++n) enumerate(a,n);
    invalid({},1); invalid({1},0); invalid({1},-1); invalid({1,2},3);
    a.assign(100000,10000);
    check(a,50000,std::vector<int>(50001,10000)); check(a,100000,{10000}); check(a,1,a);
    a.clear(); std::vector<int> expected;
    for (int x=10000;x>=-10000;--x) a.push_back(x);
    for (int i=0;i<19502;++i) expected.push_back(a[i]);
    check(a,500,expected);
    std::cout << "LC239: fixed, exhaustive window-oracle, invalid and limit cases passed\n";
}
