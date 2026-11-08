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
using Partition=std::vector<std::string>;
using Partitions=std::set<Partition>;
bool palindrome(const std::string& word) {return std::equal(word.begin(),word.end(),word.rbegin());}
Partitions oracle(const std::string& text) {
    if (text.empty()) return {Partition{}};
    Partitions result;
    for (unsigned mask=0; mask<(1U<<(text.size()-1)); ++mask) {
        Partition pieces;std::size_t begin=0;bool valid=true;
        for (std::size_t end=0; end<text.size(); ++end) if (end+1==text.size() || ((mask>>end)&1U)) {
            const auto piece=text.substr(begin,end-begin+1);
            if (!palindrome(piece)) {valid=false;break;}
            pieces.push_back(piece);begin=end+1;
        }
        if (valid) result.insert(pieces);
    }
    return result;
}
void validate(const std::string& text,const std::vector<Partition>& output) {
    const Partitions unique(output.begin(),output.end());check(unique.size()==output.size(),"duplicate partition");
    for (const auto& partition:output) {
        std::string joined;
        for (const auto& piece:partition) {check(!piece.empty() && palindrome(piece),"nonempty palindrome pieces");joined+=piece;}
        check(joined==text,"partition concatenation");
    }
}
void verify(const std::string& text,const Partitions& expected) {
    lab::Solution solution;const auto output=solution.partition(text);
    check(Partitions(output.begin(),output.end())==expected,"complete palindrome partition set");validate(text,output);
}
int main() {
    verify("noon",{{"n","o","o","n"},{"n","oo","n"},{"noon"}});
    for (unsigned length=0; length<=7; ++length) for (unsigned code=0; code<(1U<<length); ++code) {
        std::string text;
        for (unsigned i=0; i<length; ++i) text.push_back(((code>>i)&1U)?'a':'b');
        verify(text,oracle(text));
    }
    lab::Solution solution;const std::string largest(16,'a');const auto output=solution.partition(largest);
    check(output.size()==32768,"maximum partition count");validate(largest,output);
    std::cout << "Palindrome partitions: passed\n";
}
