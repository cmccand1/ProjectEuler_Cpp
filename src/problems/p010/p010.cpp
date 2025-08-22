#include "euler/problem.hpp"
#include <string>

#include "euler/util.hpp"

class P010 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Summation of Primes";
    }

    [[nodiscard]] std::string solve() override {
      constexpr int num = 2'000'000;
      auto sieve = sieve_of_eratosthenes(2'000'000);
      size_t sum = 2;
      for (size_t i = 3; i < num; i += 2) {
        if (sieve[i]) sum += i;
      }
      return std::to_string(sum);
    }
};

const REGISTER_PROBLEM(10, P010);
