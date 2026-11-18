#include "lesson.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& why) {
    if (!ok) { std::cerr << why << '\n'; std::exit(EXIT_FAILURE); }
}
template<class Error, class F> void throws(F operation) {
    bool caught = false;
    try { operation(); } catch (const Error&) { caught = true; }
    require(caught, "expected exception missing");
}

int oracle(const std::vector<int>& a) {
    int best=0;
    for (unsigned mask=0;mask<(1U<<a.size());++mask) {
        bool valid=true; int sum=0;
        for (std::size_t i=0;i<a.size();++i) if ((mask & (1U<<i))!=0) {
            if (a.size()>1 && (mask & (1U<<((i+1)%a.size())))!=0) valid=false;
            sum+=a[i];
        }
        if (valid) best=std::max(best,sum);
    }
    return best;
}
void check(std::vector<int> a,int expected) {
    const auto before=a;
    require(lab::Solution{}.rob(a)==expected,"circular robbery maximum differs");
    require(a==before,"house input changed");
}
int main() {
    check({8,1,1,8},9); check({9},9); check({4,7},7);
    check({5,1,5},5); check({2,8,2,8,2},16); check({0,0,0},0); check({},0);
    for (int length=0;length<=7;++length) {
        const unsigned count=1U<<(2*length);
        for (unsigned encoding=0;encoding<count;++encoding) {
            std::vector<int> a(length); unsigned bits=encoding;
            for (auto& value:a) { value=static_cast<int>(bits%4); bits/=4; }
            check(a,oracle(a));
        }
    }
    check(std::vector<int>(100,1000),50000);
    std::vector<int> ends(100,0); ends.front()=1000; ends.back()=999; check(ends,1000);
    std::cout << "LC213: fixed, 21845 subset-oracle and limit cases passed\n";
}
