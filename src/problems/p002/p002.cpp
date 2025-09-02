#include <string>
#include <valarray>

#include "euler/problem.hpp"
#include "euler/util.hpp"

class P002 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Even Fibonacci Numbers";
    }

    [[nodiscard]] std::string solve() override {
      constexpr std::size_t N = 4'000'000;
      std::size_t sum = 0, result = 0;
      for (std::size_t i = 0; (result = fib(i)) < N; ++i) {
        if (result % 2 == 0) sum += result;
      }
      return std::to_string(sum);
    }
};

const REGISTER_PROBLEM(
  002,
  P002
);
