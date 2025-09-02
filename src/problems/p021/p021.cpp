#include <vector>
#include <string>
#include "euler/problem.hpp"

class P021 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Amicable Numbers";
    }

    [[nodiscard]] std::string solve() override {
      constexpr std::size_t N = 10'000;

      // sum_divs[n] = sum of proper divisors of n
      std::vector<std::size_t> sum_divs(N, 0);
      // Start from 1 (proper divisor for all multiples >= 2)
      for (std::size_t d = 1; d < N / 2 + 1; ++d) {
        for (std::size_t multiple = d * 2; multiple < N; multiple += d) {
          sum_divs[multiple] += d;
        }
      }

      std::size_t amicable_sum = 0;
      for (std::size_t i = 2; i < N; ++i) {
        if (const std::size_t s = sum_divs[i];
          s != i && s < N && sum_divs[s] == i) {
          amicable_sum += i;
        }
      }
      return std::to_string(amicable_sum);
    }
};

const REGISTER_PROBLEM(21, P021);
