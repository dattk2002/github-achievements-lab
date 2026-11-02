#pragma once

namespace lab {

inline unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        const unsigned long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

}  // namespace lab
