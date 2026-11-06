#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <string>
int oracle(const std::string& a,const std::string& b,std::size_t i=0,std::size_t j=0) {
    if (i==a.size()) return static_cast<int>(b.size()-j);
    if (j==b.size()) return static_cast<int>(a.size()-i);
    if (a[i]==b[j]) return oracle(a,b,i+1,j+1);
    return 1+std::min({oracle(a,b,i+1,j),oracle(a,b,i,j+1),oracle(a,b,i+1,j+1)});
}
void verify(const std::string& a,const std::string& b,int expected) {
    lab::Solution solution;
    check(solution.minDistance(a,b)==expected,"unit edit distance");
}
int main() {
    verify("stone","tones",2); verify("","",0); verify("","mint",4); verify("mint","",4);
    verify("ab","ba",2); verify("abc","adc",1); verify("abcd","acd",1); verify("abc","abxc",1);
    std::vector<std::string> words;
    for (unsigned length=0; length<=4; ++length)
        for (unsigned code=0; code<(1U<<length); ++code) {
            std::string word;
            for (unsigned i=0; i<length; ++i) word.push_back(((code>>i)&1U) ? 'a' : 'b');
            words.push_back(word);
        }
    for (const auto& a:words) for (const auto& b:words) verify(a,b,oracle(a,b));
    verify(std::string(500,'a'),std::string(500,'b'),500);
    verify(std::string(500,'a'),"",500);
    verify(std::string(500,'a'),std::string(499,'a')+'b',1);
    std::cout << "Edit distance: passed\n";
}
