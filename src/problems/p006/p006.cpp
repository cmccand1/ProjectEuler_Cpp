#include "euler/problem.hpp"
#include <string>

#include "euler/util.hpp"

class P006 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Sum Square Difference";
    }

    std::string solve() override {
      const int square_of_sums = static_cast<int>(std::pow(natural_sum(100), 2));
      const int sum_squares = sum_of_squares(100);
      return std::to_string(square_of_sums - sum_squares);
    }
};

const REGISTER_PROBLEM(6, P006);
