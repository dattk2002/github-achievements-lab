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

// Enumerate every task order; schedule each order at its earliest legal times.
int oracle(std::vector<char> tasks,int cooldown) {
    if (tasks.empty()) return 0;
    std::sort(tasks.begin(),tasks.end());
    int best=std::numeric_limits<int>::max();
    do {
        std::array<int,26> next{}; int time=0;
        for (char task:tasks) {
            const auto index=static_cast<std::size_t>(task-'A');
            time=std::max(time,next[index]);
            next[index]=time+cooldown+1; ++time;
        }
        best=std::min(best,time);
    } while (std::next_permutation(tasks.begin(),tasks.end()));
    return best;
}
void check(std::vector<char> tasks,int cooldown,int expected) {
    const auto before=tasks;
    require(lab::Solution{}.leastInterval(tasks,cooldown)==expected,"schedule length differs");
    require(tasks==before,"tasks input changed");
}
int main() {
    check({'A','A','A','A','B','B','C'},2,10);
    check({'A','A','B','B','C','C'},3,7);
    check({'Z','Z','Z'},4,11); check({'X','Y','Z'},100,3);
    check({'A','A','B'},0,3); check({},4,0);
    for (int a=0;a<=2;++a) for (int b=0;b<=2;++b) for (int c=0;c<=2;++c)
        for (int cooldown=0;cooldown<=3;++cooldown) {
            std::vector<char> tasks(a,'A'); tasks.insert(tasks.end(),b,'B'); tasks.insert(tasks.end(),c,'C');
            check(tasks,cooldown,oracle(tasks,cooldown));
        }
    check(std::vector<char>(10000,'A'),100,1009900);
    std::vector<char> all;
    for (int r=0;r<300;++r) for (char task='A';task<='Z';++task) all.push_back(task);
    check(all,25,7800); check(all,26,8099);
    for (int cooldown: {-1,101}) {
        std::vector<char> tasks{'A'};
        throws<std::invalid_argument>([&] { (void)lab::Solution{}.leastInterval(tasks,cooldown); });
    }
    for (char bad: {'a','@','['}) {
        std::vector<char> tasks{'A',bad}; const auto before=tasks;
        throws<std::invalid_argument>([&] { (void)lab::Solution{}.leastInterval(tasks,2); });
        require(tasks==before,"invalid tasks changed");
    }
    std::cout << "LC621: fixed, 108 permutation-oracle and limit cases passed\n";
}
