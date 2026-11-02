#pragma once

#include <cstdint>
#include <functional>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace lab {

using Cents = std::int64_t;
using DiscountPolicy = std::function<Cents(Cents)>;

class Checkout {
public:
    explicit Checkout(DiscountPolicy discount = [](Cents) { return Cents{0}; })
        : discount_(std::move(discount)) {
        if (!discount_) {
            throw std::invalid_argument("discount policy must be callable");
        }
    }

    Cents total(const std::vector<Cents>& prices) const {
        Cents subtotal = 0;
        for (Cents price : prices) {
            if (price < 0) {
                throw std::invalid_argument("price must be nonnegative");
            }
            // Check before addition: signed overflow would be undefined behavior.
            if (price > std::numeric_limits<Cents>::max() - subtotal) {
                throw std::overflow_error("subtotal exceeds Cents range");
            }
            subtotal += price;
        }
        const Cents discount = discount_(subtotal);
        if (discount < 0 || discount > subtotal) {
            throw std::invalid_argument("discount must be within subtotal");
        }
        return subtotal - discount;
    }

private:
    DiscountPolicy discount_;
};

}  // namespace lab
