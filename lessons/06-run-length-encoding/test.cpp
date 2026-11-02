#include "lesson.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
void check(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}
#include <stdexcept>
#include <string>
int main() {
    using Runs = std::vector<std::pair<char, std::size_t>>;
    check(lab::encode_runs("aaabbcaa") == Runs{{'a',3},{'b',2},{'c',1},{'a',2}}, "run boundaries/counts");
    check(lab::encode_runs("").empty(), "empty encoding");
    check(lab::decode_runs({}).empty(), "empty decoding");
    check(lab::decode_runs({{'a',2},{'a',1},{'b',2}}) == "aaabb", "adjacent equal runs allowed");
    const std::string bytes("\0\0x\xff\xff\0", 6);
    check(lab::encode_runs(bytes) == Runs{{'\0',2},{'x',1},{static_cast<char>(0xff),2},{'\0',1}}, "binary encoding");
    check(lab::decode_runs(lab::encode_runs(bytes)) == bytes, "binary roundtrip");
    for (const Runs& runs : std::vector<Runs>{{{'z',0}}, {{'a',2},{'b',0}}}) {
        bool caught=false;
        try { (void)lab::decode_runs(runs); } catch (const std::invalid_argument&) { caught=true; }
        check(caught, "zero run rejected");
    }
    bool too_long=false;
    try { (void)lab::decode_runs({{'x',std::string{}.max_size()},{'y',1}}); }
    catch (const std::length_error&) { too_long=true; }
    check(too_long, "total size checked before allocation");
    too_long=false;
    try { (void)lab::decode_runs({{'x',std::numeric_limits<std::size_t>::max()}}); }
    catch (const std::length_error&) { too_long=true; }
    check(too_long, "oversized run rejected");
    std::string all_bytes;
    for (unsigned i=0; i<256; ++i) all_bytes.push_back(static_cast<char>(i));
    check(lab::decode_runs(lab::encode_runs(all_bytes)) == all_bytes, "every byte roundtrip");
    check(lab::encode_runs(std::string(100000,'q')) == Runs{{'q',100000}}, "long run");
    for (unsigned mask=0; mask<4096; ++mask) {
        std::string input;
        for (unsigned bit=0; bit<12; ++bit) input.push_back(((mask>>bit)&1) ? 'a' : '\0');
        const auto encoded=lab::encode_runs(input);
        check(lab::decode_runs(encoded)==input, "exhaustive binary roundtrip");
        std::size_t offset=0;
        for (std::size_t i=0; i<encoded.size(); ++i) {
            check(encoded[i].second>0 && (i==0 || encoded[i-1].first!=encoded[i].first), "canonical runs");
            for (std::size_t j=0; j<encoded[i].second; ++j) {
                check(offset<input.size() && input[offset]==encoded[i].first, "encoded bytes match input");
                ++offset;
            }
        }
        check(offset==input.size(), "encoding preserves size");
    }
    std::cout << "RLE: passed\n";
}
