#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

#include <algorithm>
#include <numeric>
using Points=std::vector<std::vector<int>>;
long long distance_squared(const std::vector<int>& p) { return 1LL*p[0]*p[0]+1LL*p[1]*p[1]; }
Points oracle(const Points& a,int k) {
    std::vector<std::size_t> indices(a.size());std::iota(indices.begin(),indices.end(),0);
    std::sort(indices.begin(),indices.end(),[&](auto i,auto j) {
        if(distance_squared(a[i])!=distance_squared(a[j])) return distance_squared(a[i])<distance_squared(a[j]);
        return i<j;
    });
    Points selected;
    for(int i=0;i<k;++i) selected.push_back(a[indices[i]]);
    return selected;
}
void check(Points a,int k,Points expected) {
    const auto original=a;
    auto actual=lab::Solution{}.kClosest(a,k);
    std::sort(actual.begin(),actual.end());std::sort(expected.begin(),expected.end());
    require(actual==expected,"closest-point multiset differs");require(a==original,"points input changed");
}
void enumerate(Points& a,int remaining) {
    if(remaining==0) { for(int k=1;k<=static_cast<int>(a.size());++k) check(a,k,oracle(a,k)); return; }
    for(const auto& p:Points{{-2,0},{0,-1},{0,0},{1,0},{0,2},{1,1}}) {
        a.push_back(p);enumerate(a,remaining-1);a.pop_back();
    }
}
void invalid(Points a,int k) {
    const auto original=a;bool threw=false;
    try { (void)lab::Solution{}.kClosest(a,k); } catch(const std::invalid_argument&) { threw=true; }
    require(threw,"invalid k/point must throw");require(a==original,"invalid points changed");
}
int main() {
    check({{3,4},{0,1},{-2,0},{1,-1}},2,{{0,1},{1,-1}});
    check({{1,0},{0,1},{-1,0}},2,{{1,0},{0,1}});
    check({{1,1},{1,1},{0,0}},2,{{1,1},{0,0}});
    check({{-10000,-10000},{10000,10000},{0,1}},1,{{0,1}});
    Points a;
    for(int n=1;n<=5;++n) enumerate(a,n);
    a.assign(10000,{10000,10000});a[9999]={0,0};a[9998]={1,0};
    check(a,2,{{0,0},{1,0}});check(a,10000,a);
    invalid({},1);invalid({{0,0}},0);invalid({{0,0}},-1);invalid({{0,0}},2);
    invalid({{1}},1);invalid({{1,2,3}},1);invalid({{0,0},{}},1);
    std::cout << "LC973: fixed, 44790 sorted-oracle, tied/invalid and limit cases passed\n";
}
