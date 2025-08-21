#include "euler/problem.hpp"
#include <string>
#include "euler/util.hpp"

namespace mp = boost::multiprecision;

class P020 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Factorial Digit Sum";
    }

    std::string solve() override {
      return boost::multiprecision::to_string(digit_sum(factorial(100)));
    }

};

const REGISTER_PROBLEM(20, P020);
