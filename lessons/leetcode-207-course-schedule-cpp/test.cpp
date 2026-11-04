#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <numeric>
#include <stdexcept>
bool oracle(int n, const std::vector<std::vector<int>>& edges) {
    std::vector<int> order(static_cast<std::size_t>(n)); std::iota(order.begin(),order.end(),0);
    do {
        std::vector<int> position(static_cast<std::size_t>(n));
        for (int i=0; i<n; ++i) position[order[i]]=i;
        bool valid=true;
        for (const auto& edge:edges) if (position[edge[1]]>=position[edge[0]]) { valid=false; break; }
        if (valid) return true;
    } while (std::next_permutation(order.begin(),order.end()));
    return false;
}
void verify(int n, std::vector<std::vector<int>> edges, bool expected) {
    const auto before=edges; lab::Solution solution;
    check(solution.canFinish(n,edges)==expected,"course feasibility");
    check(edges==before,"prerequisites mutated");
}
int main() {
    verify(5,{{1,0},{2,1},{0,2}},false);
    verify(5,{{2,0},{2,1},{4,2}},true); verify(3,{},true);
    verify(1,{{0,0}},false); verify(1,{},true);
    verify(6,{{1,0},{4,3},{3,4}},false);
    verify(4,{{1,0},{2,0},{3,1},{3,2}},true);
    for (int n=1; n<=4; ++n) {
        std::vector<std::vector<int>> candidates;
        for (int a=0; a<n; ++a) for (int b=0; b<n; ++b) if (a!=b) candidates.push_back({a,b});
        for (unsigned mask=0; mask<(1U<<candidates.size()); ++mask) {
            std::vector<std::vector<int>> edges;
            for (std::size_t i=0; i<candidates.size(); ++i) if ((mask>>i)&1U) edges.push_back(candidates[i]);
            verify(n,edges,oracle(n,edges));
        }
    }
    std::vector<std::vector<int>> chain;
    for (int i=1; i<2000; ++i) chain.push_back({i,i-1});
    verify(2000,chain,true); chain.push_back({0,1999}); verify(2000,chain,false);
    std::vector<std::vector<int>> dag;
    for (int a=1; a<2000 && dag.size()<5000; ++a)
        for (int b=0; b<a && dag.size()<5000; ++b) dag.push_back({a,b});
    verify(2000,dag,true);
    const std::vector<std::vector<std::vector<int>>> invalid{{{1}},{{1,0,2}},{{-1,0}},{{2,0}}};
    for (auto edges:invalid) {
        lab::Solution solution; bool caught=false;
        try { (void)solution.canFinish(2,edges); } catch (const std::invalid_argument&) { caught=true; }
        check(caught,"malformed edge rejected");
    }
    for (int n:{0,-1}) {
        std::vector<std::vector<int>> edges; lab::Solution solution; bool caught=false;
        try { (void)solution.canFinish(n,edges); } catch (const std::invalid_argument&) { caught=true; }
        check(caught,"nonpositive course count rejected");
    }
    std::cout << "Course schedule: passed\n";
}
