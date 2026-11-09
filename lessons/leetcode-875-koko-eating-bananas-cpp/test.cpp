#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

int oracle(const std::vector<int>& a,int h) {
    int maximum=0; for (int p:a) if(p>maximum) maximum=p;
    for (int speed=1;speed<=maximum;++speed) {
        int hours=0;
        for (int p:a) { int remaining=p; while (remaining>0) { remaining-=speed; ++hours; } }
        if (hours<=h) return speed;
    }
    return maximum;
}
void check(std::vector<int> a,int h,int expected) {
    const auto original=a;
    require(lab::Solution{}.minEatingSpeed(a,h)==expected,"minimum eating speed differs");
    require(a==original,"piles input changed");
}
void enumerate(std::vector<int>& a,int remaining) {
    if(remaining==0) {
        int total=0; for (int p:a) total+=p;
        for (int h=static_cast<int>(a.size());h<=total+2;++h) check(a,h,oracle(a,h));
        return;
    }
    for(int p:{1,4,9}) { a.push_back(p); enumerate(a,remaining-1); a.pop_back(); }
}
void invalid(std::vector<int> a,int h) {
    const auto original=a; bool threw=false;
    try { (void)lab::Solution{}.minEatingSpeed(a,h); }
    catch(const std::invalid_argument&) { threw=true; }
    require(threw,"infeasible hours/empty piles must throw"); require(a==original,"invalid input changed");
}
int main() {
    check({4,9,15},8,4); check({9},2,5); check({1,1,1},10,1);
    check({1000000000},1000000000,1);
    check({1000000000,1000000000,1000000000},1000000000,4);
    std::vector<int> a;
    for(int n=1;n<=6;++n) enumerate(a,n);
    check(std::vector<int>(10000,1000000000),1000000000,10000);
    check(std::vector<int>(10000,1000000000),10000,1000000000);
    invalid({},1); invalid({2,3},1); invalid({2},0); invalid({2},-1);
    std::cout << "LC875: fixed, linear-speed oracle, invalid and limit cases passed\n";
}
