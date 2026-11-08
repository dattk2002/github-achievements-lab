#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <stdexcept>
#include <string>
int enumerate(const std::string& text,std::size_t begin) {
    if (begin==text.size()) return 1;
    if (text[begin]=='0') return 0;
    int count=enumerate(text,begin+1);
    if (begin+1<text.size()) {
        const int pair=(text[begin]-'0')*10+(text[begin+1]-'0');
        if (pair<=26) count+=enumerate(text,begin+2);
    }
    return count;
}
void verify(const std::string& text,int expected) {
    lab::Solution solution;check(solution.numDecodings(text)==expected,"decoding count and zero rules");
}
int main() {
    verify("121",3);verify("",0);verify("0",0);verify("06",0);verify("10",1);
    verify("26",2);verify("27",1);verify("210",1);verify("100",0);verify("301",0);
    const char alphabet[]{'0','1','2','7'};unsigned count=1;
    for (unsigned length=0; length<=7; ++length) {
        for (unsigned code=0; code<count; ++code) {
            unsigned value=code;std::string text;
            for (unsigned i=0; i<length; ++i) {text.push_back(alphabet[value%4]);value/=4;}
            verify(text,text.empty()?0:enumerate(text,0));
        }
        count*=4;
    }
    verify(std::string(45,'1'),1836311903);
    verify(std::string(46,'1')+'0',1836311903);
    verify(std::string(98,'1')+"30",0);
    lab::Solution solution;bool caught=false;
    try {(void)solution.numDecodings(std::string(100,'1'));} catch(const std::overflow_error&){caught=true;}
    check(caught,"out-of-guarantee final result rejected");caught=false;
    try {(void)solution.numDecodings("12x");} catch(const std::invalid_argument&){caught=true;}
    check(caught,"nondigit rejected");
    std::cout << "Decode ways: passed\n";
}
