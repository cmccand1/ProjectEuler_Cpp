#include "euler/problem.hpp"
#include <string>

#include "euler/util.hpp"

class P004 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Longest Palindromic Product";
    }

    [[nodiscard]] std::string solve() override {
      long long max_pal = -1;
      for (int i = 999; i > 99; --i) {
        for (int j = i; j > 99; --j) {
          const long long product = i * j;
          if (product <= max_pal) break;
          if (is_palindrome_fast(product)) {
            max_pal = product;
          }
        }
      }
      return std::to_string(max_pal);
    }
};

const REGISTER_PROBLEM (
4
,
P004
);