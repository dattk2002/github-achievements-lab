#include "lesson.hpp"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
void check(bool ok, const char* message) {
    if (!ok) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(1);
    }
}

template <typename Exception, typename Action>
void rejects(Action action, const char* message) {
    try {
        action();
    } catch (const Exception&) {
        return;
    } catch (...) {
        check(false, "wrong exception type");
    }
    check(false, message);
}
}  // namespace

int main() {
    using lab::Cents;
    const Cents max = std::numeric_limits<Cents>::max();
    const Cents min = std::numeric_limits<Cents>::min();
    const lab::Checkout regular;
    check(regular.total({1299, 250, 451}) == 2000, "sum all prices without discount");
    check(regular.total({}) == 0, "empty basket");
    check(regular.total({0, 0}) == 0, "zero prices");
    check(regular.total({max - 7, 7, 0}) == max, "exact maximum is valid");

    Cents coupon = 175;
    const lab::Checkout fixed([coupon](Cents) { return coupon; });
    coupon = 900;
    check(fixed.total({800, 625}) == 1250, "owned value capture and fixed discount");
    check(fixed.total({175}) == 0, "fixed discount equal to subtotal");
    rejects<std::invalid_argument>([&] { fixed.total({174}); }, "discount above subtotal");
    rejects<std::invalid_argument>([&] { fixed.total({}); }, "positive discount on empty basket");

    const lab::Checkout full([](Cents subtotal) { return subtotal; });
    check(full.total({800, 625}) == 0, "full discount");
    check(full.total({max}) == 0, "full discount at maximum");
    check(full.total({}) == 0, "full discount on empty basket");
    const lab::Checkout tenth([](Cents subtotal) { return subtotal / 10; });
    check(tenth.total({1000, 239}) == 1116, "callable receives complete subtotal");

    for (Cents bad : {Cents{-1}, min}) {
        rejects<std::invalid_argument>([&] { regular.total({5, bad}); }, "negative price");
        const lab::Checkout invalid([bad](Cents) { return bad; });
        rejects<std::invalid_argument>([&] { invalid.total({10}); }, "negative discount");
    }
    const lab::Checkout too_large([max](Cents) { return max; });
    rejects<std::invalid_argument>([&] { too_large.total({10}); }, "maximum invalid discount");
    rejects<std::invalid_argument>([] { lab::Checkout invalid(lab::DiscountPolicy{}); },
                                   "empty callable rejected");

    int calls = 0;
    const lab::Checkout counted([&calls](Cents) { ++calls; return Cents{0}; });
    check(counted.total({2, 3}) == 5 && calls == 1, "policy called once");
    check(counted.total({}) == 0 && calls == 2, "policy called for empty basket");
    rejects<std::invalid_argument>([&] { counted.total({-1}); }, "reject before policy");
    rejects<std::overflow_error>([&] { counted.total({max, 1}); }, "sum overflow");
    rejects<std::overflow_error>([&] { counted.total({max - 2, 1, 2}); },
                                 "overflow across multiple additions");
    check(calls == 2, "invalid basket never invokes policy");
    rejects<std::overflow_error>([&] { full.total({max, 1}); },
                                 "full discount cannot rescue overflow");
    const lab::Checkout throwing([](Cents) -> Cents { throw std::runtime_error("policy"); });
    rejects<std::runtime_error>([&] { throwing.total({10}); }, "policy exception propagated");
    std::cout << "Composition: passed\n";
}
