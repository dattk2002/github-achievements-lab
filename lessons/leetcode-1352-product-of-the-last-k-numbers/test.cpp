#include "lesson.hpp"

#include <cstdlib>
#include <iostream>

namespace lab {
namespace {
void check(ProductOfNumbers& stream, int k, int expected, const char* scenario) {
    const int actual = stream.getProduct(k);
    if (actual != expected) {
        std::cerr << scenario << ", k=" << k << ": expected " << expected
                  << ", got " << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}  // namespace

void run_tests() {
    ProductOfNumbers stream;
    stream.add(6);
    check(stream, 1, 6, "first value");
    stream.add(7);
    stream.add(2);
    check(stream, 2, 14, "proper suffix");
    check(stream, 3, 84, "whole stream");

    stream.add(0);
    check(stream, 1, 0, "trailing zero");
    stream.add(0);
    check(stream, 5, 0, "consecutive zeros");
    stream.add(9);
    stream.add(3);
    check(stream, 2, 27, "entire run after zero");
    check(stream, 3, 0, "suffix reaches latest zero");
    stream.add(4);
    check(stream, 3, 108, "append after queries");

    ProductOfNumbers large_product;
    for (int i = 0; i < 4; ++i) {
        large_product.add(100);
    }
    large_product.add(21);
    check(large_product, 5, 2100000000, "product near 32-bit limit");
    check(large_product, 4, 21000000, "large product suffix");

    ProductOfNumbers long_stream;
    for (int i = 0; i < 39999; ++i) {
        long_stream.add(1);
    }
    check(long_stream, 39999, 1, "largest suffix within call budget");
    std::cout << "ProductOfNumbers: 11 checks passed\n";
}
}  // namespace lab

int main() { lab::run_tests(); }
