#ifndef LAB_LEETCODE_1352_PRODUCT_OF_THE_LAST_K_NUMBERS_HPP
#define LAB_LEETCODE_1352_PRODUCT_OF_THE_LAST_K_NUMBERS_HPP

#include <cstddef>
#include <vector>

namespace lab {
class ProductOfNumbers {
public:
    void add(int num) {
        if (num == 0) {
            run_length_ = 0;
            return;
        }

        const int product = prefix_[run_length_] * num;
        const std::size_t next = run_length_ + 1;
        if (next == prefix_.size()) {
            prefix_.push_back(product);
        } else {
            prefix_[next] = product;
        }
        run_length_ = next;
    }

    int getProduct(int k) {
        const auto count = static_cast<std::size_t>(k);
        if (count > run_length_) {
            return 0;
        }
        return prefix_[run_length_] / prefix_[run_length_ - count];
    }

private:
    // Entries beyond run_length_ can be reused by the next run.
    std::vector<int> prefix_{1};
    std::size_t run_length_ = 0;
};
}  // namespace lab

#endif
