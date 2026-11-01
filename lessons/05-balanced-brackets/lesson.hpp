#pragma once

#include <string>
#include <string_view>

namespace lab {

inline bool balanced_brackets(std::string_view text) {
    std::string pending;
    for (char ch : text) {
        switch (ch) {
            case '(': pending.push_back(')'); break;
            case '[': pending.push_back(']'); break;
            case '{': pending.push_back('}'); break;
            case ')': case ']': case '}':
                if (pending.empty() || pending.back() != ch) return false;
                pending.pop_back();
                break;
            default: break;
        }
    }
    return pending.empty();
}

}  // namespace lab
