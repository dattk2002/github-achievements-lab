#include "lesson.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <queue>
#include <stdexcept>
bool connected_without(const std::vector<std::vector<int>>& edges,int n,std::size_t ignored) {
    std::vector<std::vector<int>> adjacent(static_cast<std::size_t>(n)+1);
    for (std::size_t i=0; i<edges.size(); ++i) if (i!=ignored) {
        adjacent[edges[i][0]].push_back(edges[i][1]); adjacent[edges[i][1]].push_back(edges[i][0]);
    }
    std::queue<int> ready;ready.push(1);std::vector<bool> seen(static_cast<std::size_t>(n)+1,false);seen[1]=true;int count=0;
    while (!ready.empty()) {
        const int node=ready.front();ready.pop();++count;
        for (int next:adjacent[node]) if (!seen[next]) { seen[next]=true;ready.push(next); }
    }
    return count==n;
}
std::vector<int> oracle(const std::vector<std::vector<int>>& edges) {
    std::vector<int> answer; const int n=static_cast<int>(edges.size());
    for (std::size_t i=0; i<edges.size(); ++i) if (connected_without(edges,n,i)) answer=edges[i];
    return answer;
}
void verify(std::vector<std::vector<int>> edges,const std::vector<int>& expected) {
    const auto before=edges;lab::Solution solution;
    check(solution.findRedundantConnection(edges)==expected,"last removable cycle edge");
    check(edges==before,"edges mutated");
}
int main() {
    verify({{1,2},{1,3},{2,4},{3,4}},{3,4});verify({},{});
    verify({{1,2},{1,3},{2,3},{3,4},{4,5}},{2,3});
    for (int n=3; n<=5; ++n) {
        std::vector<std::vector<int>> candidates;
        for (int u=1; u<=n; ++u) for (int v=u+1; v<=n; ++v) candidates.push_back({u,v});
        for (unsigned mask=0; mask<(1U<<candidates.size()); ++mask) {
            std::vector<std::vector<int>> edges;
            for (std::size_t i=0; i<candidates.size(); ++i) if ((mask>>i)&1U) edges.push_back(candidates[i]);
            if (edges.size()!=static_cast<std::size_t>(n) || !connected_without(edges,n,edges.size())) continue;
            for (int offset=0; offset<n; ++offset) {
                auto rotated=edges;std::rotate(rotated.begin(),rotated.begin()+offset,rotated.end());
                verify(rotated,oracle(rotated));std::reverse(rotated.begin(),rotated.end());verify(rotated,oracle(rotated));
            }
        }
    }
    std::vector<std::vector<int>> large;
    for (int i=1; i<1000; ++i) large.push_back({i,i+1});
    large.push_back({1,1000});verify(large,{1,1000});
    for (auto edges:std::vector<std::vector<std::vector<int>>>{{{1}},{{0,1}},{{1,2}}}) {
        lab::Solution solution;bool caught=false;
        try {(void)solution.findRedundantConnection(edges);} catch(const std::invalid_argument&){caught=true;}
        check(caught,"malformed edge or endpoint rejected");
    }
    std::cout << "Redundant connection: passed\n";
}
