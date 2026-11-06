#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <set>
#include <string>
std::string oracle(const std::string& s,const std::string& t) {
    if (t.empty()) return "";
    std::string best;
    for (std::size_t left=0; left<s.size(); ++left) {
        std::multiset<char> needed(t.begin(),t.end());
        for (std::size_t right=left; right<s.size(); ++right) {
            const auto match=needed.find(s[right]);
            if (match!=needed.end()) needed.erase(match);
            if (needed.empty()) {
                if (best.empty() || right-left+1<best.size()) best=s.substr(left,right-left+1);
                break;
            }
        }
    }
    return best;
}
std::vector<std::string> words(unsigned max_length) {
    std::vector<std::string> result;
    unsigned count=1;
    for (unsigned length=0; length<=max_length; ++length) {
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code; std::string word;
            for (unsigned i=0; i<length; ++i) { word.push_back("abc"[value%3]); value/=3; }
            result.push_back(word);
        }
        count*=3;
    }
    return result;
}
void verify(const std::string& s,const std::string& t,const std::string& expected) {
    lab::Solution solution;
    check(solution.minWindow(s,t)==expected,"minimum covering window including multiplicities");
}
int main() {
    verify("xxaabzycaab","aabc","caab"); verify("ababac","aabc","abac");
    verify("abc","aaabc",""); verify("abc","",""); verify("","a",""); verify("","","");
    verify("abca","ac","ca"); verify("ababa","ab","ab"); verify("AaA","aa","");
    verify(std::string("a\0b\0c",5),std::string("\0c",2),std::string("\0c",2));
    const char high=static_cast<char>(0xff);
    verify(std::string{high,'A',high,'B'},std::string{high,'B'},std::string{high,'B'});
    const auto sources=words(5),targets=words(3);
    for (const auto& s:sources) for (const auto& t:targets) verify(s,t,oracle(s,t));
    std::string long_source(100000,'x'); long_source.front()='a';long_source.back()='b';
    verify(long_source,"ab",long_source);
    verify(std::string(100000,'a'),std::string(100000,'a'),std::string(100000,'a'));
    std::cout << "Minimum window: passed\n";
}
