#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

bool oracle(const std::string& a,const std::string& b,const std::string& target,std::size_t i=0,std::size_t j=0) {
    if(a.size()+b.size()!=target.size()) return false;
    if(i==a.size() && j==b.size()) return true;
    return (i<a.size() && a[i]==target[i+j] && oracle(a,b,target,i+1,j)) ||
           (j<b.size() && b[j]==target[i+j] && oracle(a,b,target,i,j+1));
}
void check(const std::string& a,const std::string& b,const std::string& target,bool expected) {
    require(lab::Solution{}.isInterleave(a,b,target)==expected,"interleave result differs");
}
std::string word(unsigned mask,int length) {
    std::string result;
    for(int i=0;i<length;++i) result+=((mask & (1U<<i))!=0) ? 'a':'b';
    return result;
}
int main() {
    check("ab","cd","acbd",true); check("ab","cd","abdc",false);
    check("aab","aac","aaaabc",true); check("ab","ac","abca",false);
    check("","","",true); check("abc","","abc",true); check("","abc","abc",true);
    check("a","b","a",false); check("a","b","abb",false);
    for(int n=0;n<=3;++n) for(int m=0;m<=3;++m)
        for(unsigned x=0;x<(1U<<n);++x) for(unsigned y=0;y<(1U<<m);++y)
            for(unsigned z=0;z<(1U<<(n+m));++z) {
                const auto a=word(x,n),b=word(y,m),target=word(z,n+m);
                check(a,b,target,oracle(a,b,target));
            }
    check(std::string(100,'a'),std::string(100,'b'),std::string(100,'a')+std::string(100,'b'),true);
    check(std::string(100,'a'),std::string(100,'b'),std::string(100,'a')+std::string(99,'b')+"c",false);
    check(std::string(100,'a'),std::string(100,'a'),std::string(200,'a'),true);
    std::cout << "LC97: fixed, 7225 recursive-oracle and limit cases passed\n";
}
