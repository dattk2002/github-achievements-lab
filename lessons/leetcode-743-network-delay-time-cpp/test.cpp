#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <stdexcept>
int oracle(const std::vector<std::vector<int>>& edges,int n,int source) {
    const int inf=1000000;
    std::vector<std::vector<int>> dist(static_cast<std::size_t>(n),std::vector<int>(static_cast<std::size_t>(n),inf));
    for (int i=0; i<n; ++i) dist[i][i]=0;
    for (const auto& edge:edges) dist[edge[0]-1][edge[1]-1]=edge[2];
    for (int middle=0; middle<n; ++middle) for (int i=0; i<n; ++i) for (int j=0; j<n; ++j)
        dist[i][j]=std::min(dist[i][j],dist[i][middle]+dist[middle][j]);
    const int maximum=*std::max_element(dist[source-1].begin(),dist[source-1].end());
    return maximum==inf ? -1 : maximum;
}
void verify(std::vector<std::vector<int>> edges,int n,int source,int expected) {
    const auto before=edges; lab::Solution solution;
    check(solution.networkDelayTime(edges,n,source)==expected,"directed network delay");
    check(edges==before,"edges mutated");
}
int main() {
    verify({{1,2,8},{1,3,1},{3,2,1},{2,4,2}},4,1,4);
    verify({},1,1,0); verify({},3,2,-1); verify({{1,2,1}},2,2,-1);
    verify({{1,2,0},{2,1,0},{2,3,0}},3,1,0);
    verify({{4,2,3},{2,1,2},{1,3,1}},4,4,6);
    std::vector<std::vector<int>> candidates;
    for (int u=1; u<=3; ++u) for (int v=1; v<=3; ++v) if (u!=v) candidates.push_back({u,v});
    for (unsigned code=0; code<729; ++code) {
        unsigned value=code; std::vector<std::vector<int>> edges;
        for (const auto& pair:candidates) {
            const unsigned choice=value%3;value/=3;
            if (choice) edges.push_back({pair[0],pair[1],choice==1 ? 0 : 3});
        }
        for (int source=1; source<=3; ++source) verify(edges,3,source,oracle(edges,3,source));
    }
    std::vector<std::vector<int>> chain;
    for (int i=1; i<100; ++i) chain.push_back({i,i+1,100});
    verify(chain,100,1,9900);
    std::vector<std::vector<int>> dense;
    for (int u=1; u<=100 && dense.size()<6000; ++u)
        for (int v=1; v<=100 && dense.size()<6000; ++v) if (u!=v) dense.push_back({u,v,0});
    verify(dense,100,1,0);
    const std::vector<std::vector<std::vector<int>>> invalid{{{1,2}},{{1,2,0,3}},{{0,2,1}},{{1,3,1}},{{1,2,-1}}};
    for (auto edges:invalid) {
        lab::Solution solution; bool caught=false;
        try { (void)solution.networkDelayTime(edges,2,1); } catch (const std::invalid_argument&) { caught=true; }
        check(caught,"invalid edge rejected");
    }
    for (const auto& nk:std::vector<std::vector<int>>{{0,1},{-1,1},{2,0},{2,3}}) {
        std::vector<std::vector<int>> edges; lab::Solution solution; bool caught=false;
        try { (void)solution.networkDelayTime(edges,nk[0],nk[1]); } catch (const std::invalid_argument&) { caught=true; }
        check(caught,"invalid n/source rejected");
    }
    std::cout << "Network delay: passed\n";
}
