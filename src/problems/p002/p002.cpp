#include <string>
#include <valarray>

#include "euler/problem.hpp"
#include "euler/util.hpp"

class P002 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Even Fibonacci Numbers";
    }

    std::string solve() override {
      long long sum = 0, result = 0;
      for (int i = 0; (result = fib(i)) < 4000000; ++i) {
        if (result % 2 == 0) sum += result;
      }
      return std::to_string(sum);
    }
};

const REGISTER_PROBLEM(002, P002);
