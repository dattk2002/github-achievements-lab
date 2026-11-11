#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
void require(bool ok, const std::string& message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}

using Graph=std::vector<std::vector<int>>;
bool oracle(const Graph& graph) {
    for(unsigned mask=0;mask<(1U<<graph.size());++mask) {
        bool valid=true;
        for(std::size_t u=0;u<graph.size() && valid;++u) for(int v:graph[u])
            if(((mask>>u)&1U)==((mask>>v)&1U)) { valid=false;break; }
        if(valid) return true;
    }
    return false;
}
void edge(Graph& a,int u,int v) { a[u].push_back(v);a[v].push_back(u); }
void check(Graph a,bool expected) {
    const auto original=a;
    require(lab::Solution{}.isBipartite(a)==expected,"bipartite result differs");
    require(a==original,"graph input changed");
}
void invalid(Graph a) {
    const auto original=a;bool threw=false;
    try { (void)lab::Solution{}.isBipartite(a); } catch(const std::invalid_argument&) { threw=true; }
    require(threw,"invalid neighbor must throw");require(a==original,"invalid graph changed");
}
int main() {
    check({{1,2,3,4},{0},{0},{0},{0}},true);
    check({{1,2},{0,2},{0,1}},false);check({},true);check({{}},true);check({{0}},false);
    for(int n=0;n<=6;++n) {
        const int edges=n*(n-1)/2;
        for(unsigned mask=0;mask<(1U<<edges);++mask) {
            Graph a(n);int bit=0;
            for(int u=0;u<n;++u) for(int v=u+1;v<n;++v,++bit)
                if((mask & (1U<<bit))!=0) edge(a,u,v);
            check(a,oracle(a));
        }
    }
    Graph a(100);
    for(int u=0;u<99;++u) edge(a,u,u+1);
    check(a,true);edge(a,0,2);check(a,false);
    a.assign(100,{});
    for(int u=0;u<50;++u) for(int v=50;v<100;++v) edge(a,u,v);
    check(a,true);edge(a,0,1);check(a,false);
    a.assign(100,{});for(int u=0;u<89;++u) edge(a,u,u+1);
    edge(a,97,98);edge(a,98,99);edge(a,99,97);check(a,false);
    invalid({{-1}});invalid({{1}});invalid({{}, {2}});
    std::cout << "LC785: fixed, 33868 partition-oracle, invalid and limit cases passed\n";
}
