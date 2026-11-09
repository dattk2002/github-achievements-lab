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
    int best=a.front();
    for (std::size_t left=0;left<a.size();++left) {
        int product=1;
        for (std::size_t right=left;right<a.size();++right) {
            product*=a[right]; if (product>best) best=product;
        }
    }
    return best;
}
void check(std::vector<int> a,int expected) {
    const auto original=a;
    require(lab::Solution{}.maxProduct(a)==expected,"maximum product differs");
    require(a==original,"product input changed");
}
void enumerate(std::vector<int>& a,int remaining) {
    if (remaining==0) { check(a,oracle(a)); return; }
    for (int x : {-2,-1,0,1,2}) { a.push_back(x); enumerate(a,remaining-1); a.pop_back(); }
}
int main() {
    check({-3,2,-4,0,5},24); check({-2},-2); check({-2,0,-1},0);
    check({-2,-3,0,-2,-4},8);
    std::vector<int> a;
    for (int n=1;n<=7;++n) enumerate(a,n);
    check(std::vector<int>(30,2),1073741824);
    check(std::vector<int>(20000,1),1); check(std::vector<int>(20000,0),0);
    check(std::vector<int>(20000,-1),1);
    bool threw=false;
    try { (void)lab::Solution{}.maxProduct(a); } catch (const std::invalid_argument&) { threw=true; }
    require(threw,"empty product input must throw"); require(a.empty(),"empty input changed");
    std::cout << "LC152: fixed, 97655 subarray-oracle, empty and limit cases passed\n";
}
