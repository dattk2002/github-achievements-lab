#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace lab {
class Solution {
public:
    std::vector<int> partitionLabels(const std::string& text) {
        for (unsigned char letter : text)
            if (letter < 'a' || letter > 'z') throw std::invalid_argument("only a-z is supported");
        std::array<std::size_t, 26> last{};
        for (std::size_t i = 0; i < text.size(); ++i) last[text[i] - 'a'] = i;
        std::vector<int> lengths;
        std::size_t begin = 0, end = 0;
        for (std::size_t i = 0; i < text.size(); ++i) {
            end = std::max(end, last[text[i] - 'a']);
            if (i == end) {
                lengths.push_back(static_cast<int>(i - begin + 1));
                begin = i + 1;
            }
        }
        return lengths;
    }
};
}  // namespace lab
