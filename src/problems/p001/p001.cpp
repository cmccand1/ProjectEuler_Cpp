#include "euler/problem.hpp"
#include <string>

class P001 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Multiples of 3 or 5";
    }

    std::string solve() override {
      long long sum = 0;
      for (int i = 1; i < 1000; ++i) {
        if (i % 3 == 0 || i % 5 == 0) {
          sum += i;
        }
      }
      return std::to_string(sum);
    }
};

const REGISTER_PROBLEM(001, P001);
