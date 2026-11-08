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
bool oracle(const std::string& text,const std::set<std::string>& dictionary,std::size_t begin=0) {
    if (begin==text.size()) return true;
    for (std::size_t end=begin+1; end<=text.size(); ++end)
        if (dictionary.count(text.substr(begin,end-begin)) && oracle(text,dictionary,end)) return true;
    return false;
}
void verify(const std::string& text,std::vector<std::string> dictionary,bool expected) {
    const auto before=dictionary;lab::Solution solution;
    check(solution.wordBreak(text,dictionary)==expected,"dictionary segmentation");
    check(dictionary==before,"dictionary mutated");
}
int main() {
    verify("gridpathgrid",{"grid","path"},true);verify("cars",{"car","ca","rs"},true);
    verify("redbluegreen",{"red","blue"},false);verify("redred",{"red"},true);
    verify("",{},true);verify("a",{},false);
    const std::vector<std::string> pool{"a","b","aa","ab","ba","bb"};
    for (unsigned mask=0; mask<64; ++mask) {
        std::vector<std::string> dictionary;
        for (unsigned i=0; i<6; ++i) if ((mask>>i)&1U) dictionary.push_back(pool[i]);
        const std::set<std::string> independent(dictionary.begin(),dictionary.end());
        for (unsigned length=0; length<=7; ++length) for (unsigned code=0; code<(1U<<length); ++code) {
            std::string text;
            for (unsigned i=0; i<length; ++i) text.push_back(((code>>i)&1U) ? 'a':'b');
            verify(text,dictionary,oracle(text,independent));
        }
    }
    verify(std::string(300,'a'),{std::string(20,'a')},true);
    verify(std::string(299,'a')+'b',{"a","aa","aaa"},false);
    std::vector<std::string> many;
    for (unsigned code=0; code<1000; ++code) {
        unsigned value=code;std::string word;
        for (unsigned i=0; i<3; ++i) {word.push_back(static_cast<char>('a'+value%26));value/=26;}
        many.push_back(word);
    }
    verify(std::string(300,'a'),many,true);
    std::cout << "Word break: passed\n";
}
