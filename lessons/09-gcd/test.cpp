#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <numeric>
int main() {
    using U=unsigned long long;
    check(lab::gcd(18,30)==6, "shared divisor");
    check(lab::gcd(0,0)==0, "both zero");
    check(lab::gcd(0,35)==35 && lab::gcd(35,0)==35, "one zero");
    check(lab::gcd(17,17)==17, "equal");
    check(lab::gcd(25,49)==1 && lab::gcd(42,7)==7, "coprime and divisible");
    const U max=std::numeric_limits<U>::max();
    check(lab::gcd(max,max)==max && lab::gcd(max,0)==max, "largest unsigned");
    check(lab::gcd(max,max-1)==1 && lab::gcd(max,1)==1, "large coprime without subtraction loop");
    for (U a=0; a<=250; ++a) for (U b=0; b<=250; ++b)
        check(lab::gcd(a,b)==std::gcd(a,b), "small oracle");
    const std::vector<U> edges{0,1,2,3,97,1024,max,max-1,max/2,max/2+1};
    for (U a:edges) for (U b:edges) check(lab::gcd(a,b)==std::gcd(a,b), "edge oracle");
    U a=1,b=1;
    while (a<=max-b) { const U next=a+b; a=b; b=next; }
    check(lab::gcd(a,b)==1, "large consecutive Fibonacci values");
    std::cout << "GCD: passed\n";
}
