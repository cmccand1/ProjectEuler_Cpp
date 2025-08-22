#include "euler/problem.hpp"
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

#include "euler/util.hpp"

class P016 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Power Digit Sum";
    }


    [[nodiscard]] std::string solve() override {
      using boost::multiprecision::cpp_int;
      const cpp_int base = 2;
      constexpr int exponent = 1000;
      const cpp_int result = boost::multiprecision::pow(base, exponent);

      return boost::multiprecision::to_string(digit_sum(result));
    }
};

const REGISTER_PROBLEM (
16
,
P016
);