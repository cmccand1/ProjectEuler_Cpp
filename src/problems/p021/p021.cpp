#include <cassert>
#include <iostream>

#include "euler/problem.hpp"
#include <string>

class P021 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Amicable Numbers";
    }

    [[nodiscard]] std::string solve() override {
      constexpr std::size_t N = 10'000;

      // pds[n] = proper divisors of n
      std::vector<unsigned long> pds(N, 0);
      // for every number less than N
      for (std::size_t i = 0; i < N; ++i) {
        // sum the proper divisors of that number and store in the table
        for (std::size_t j = 0; j < i; ++j) {
          if (i % j == 0) pds[i] += j;
        }
      }

      // find the amicable sum < N
      std::size_t amicable_sum = 0;
      for (std::size_t i = 0; i < N; ++i) {
        if (i != pds[i] && i == pds[pds[i]]) {
          amicable_sum += i;
        }
      }
      return std::to_string(amicable_sum);
    }
};

const REGISTER_PROBLEM(21, P021);
