#include "euler/problem.hpp"
#include <string>

#include "euler/util.hpp"

class P004 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Longest Palindromic Product";
    }

    [[nodiscard]] std::string solve() override {
      constexpr int THREE_DIGIT_MAX = 999;
      constexpr int THREE_DIGIT_MIN = 100;

      long long max_product = -1;
      for (int i = THREE_DIGIT_MAX; i >= THREE_DIGIT_MIN; --i) {
        for (int j = i; j >= THREE_DIGIT_MIN; --j) {
          const long long product = i * j;
          if (product <= max_product) break; // ensure next work is worth it
          if (is_palindrome_fast(product)) {
            max_product = product;
          }
        }
      }
      return std::to_string(max_product);
    }
};

const REGISTER_PROBLEM(
  4,
  P004
);
