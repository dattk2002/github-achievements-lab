#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(EXIT_FAILURE); }
}
// BFS finds the shortest sum of squares, independently of the production DP.
std::vector<int> distances(int limit) {
    std::vector<int> distance(static_cast<std::size_t>(limit + 1), -1);
    std::queue<int> pending;
    pending.push(0);
    distance[0] = 0;
    while (!pending.empty()) {
        const int sum = pending.front();
        pending.pop();
        for (int root = 1; root * root <= limit - sum; ++root) {
            const int next = sum + root * root;
            if (distance[next] != -1) continue;
            distance[next] = distance[sum] + 1;
            pending.push(next);
        }
    }
    return distance;
}
int main() {
    lab::Solution solution;
    require(solution.numSquares(18) == 2, "18 = 9 + 9");
    require(solution.numSquares(28) == 4, "28 needs four squares");
    require(solution.numSquares(1) == 1, "smallest source input");
    require(solution.numSquares(0) == 0, "empty sum extension");
    const auto expected = distances(500);
    for (int n = 0; n <= 500; ++n)
        require(solution.numSquares(n) == expected[n], "BFS oracle mismatch");
    require(solution.numSquares(9999) == 4, "upper four-square case");
    require(solution.numSquares(10000) == 1, "upper perfect square");
    for (int invalid : {-1, 10001}) {
        bool caught = false;
        try { (void)solution.numSquares(invalid); }
        catch (const std::invalid_argument&) { caught = true; }
        require(caught, "out-of-domain input must throw");
    }
    std::cout << "LC279: fixed, BFS oracle and boundary cases passed\n";
}
