#pragma once

#include <string>
#include <vector>

namespace lab {
class Solution {
    using Table = std::vector<std::vector<bool>>;

    static void extend(const std::string& text, std::size_t begin, const Table& palindrome,
                       std::vector<std::string>& path, std::vector<std::vector<std::string>>& result) {
        if (begin == text.size()) {
            result.push_back(path);
            return;
        }
        for (std::size_t end = begin; end < text.size(); ++end) {
            if (palindrome[begin][end]) {
                path.push_back(text.substr(begin, end - begin + 1));
                extend(text, end + 1, palindrome, path, result);
                path.pop_back();
            }
        }
    }

public:
    std::vector<std::vector<std::string>> partition(std::string s) {
        Table palindrome(s.size(), std::vector<bool>(s.size(), false));
        for (int left = static_cast<int>(s.size()) - 1; left >= 0; --left) {
            for (std::size_t right = static_cast<std::size_t>(left); right < s.size(); ++right) {
                palindrome[left][right] = s[left] == s[right] &&
                    (right - static_cast<std::size_t>(left) < 2 || palindrome[left + 1][right - 1]);
            }
        }
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> path;
        extend(s, 0, palindrome, path, result);
        return result;
    }
};
}  // namespace lab
