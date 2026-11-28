#pragma once
#include <string>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        std::string path;
        path.reserve(2 * n);
        const auto visit = [&](auto&& self, int opened, int closed) -> void {
            if (closed == n) {
                result.push_back(path);
                return;
            }
            if (opened < n) {
                path += '(';
                self(self, opened + 1, closed);
                path.pop_back();
            }
            if (closed < opened) {
                path += ')';
                self(self, opened, closed + 1);
                path.pop_back();
            }
        };
        visit(visit, 0, 0);
        return result;
    }
};
}  // namespace lab
