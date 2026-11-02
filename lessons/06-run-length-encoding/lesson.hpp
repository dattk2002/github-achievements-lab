#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace lab {

inline std::vector<std::pair<char, std::size_t>> encode_runs(std::string_view input) {
    std::vector<std::pair<char, std::size_t>> runs;
    for (char byte : input) {
        if (runs.empty() || runs.back().first != byte) {
            runs.emplace_back(byte, 1);
        } else {
            ++runs.back().second;
        }
    }
    return runs;
}

inline std::string decode_runs(
    const std::vector<std::pair<char, std::size_t>>& runs) {
    std::string result;
    std::size_t total = 0;
    // Validate every count before allocating or appending the decoded bytes.
    for (const auto& run : runs) {
        if (run.second == 0) {
            throw std::invalid_argument("Run length must be positive");
        }
        if (run.second > result.max_size() - total) {
            throw std::length_error("Decoded string exceeds max_size");
        }
        total += run.second;
    }
    result.reserve(total);
    for (const auto& run : runs) {
        result.append(run.second, run.first);
    }
    return result;
}

}  // namespace lab
