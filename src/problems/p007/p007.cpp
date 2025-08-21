#include "euler/problem.hpp"
#include "euler/util.hpp"

#include <cassert>
#include <iostream>
#include <string>

class P007 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override { return "10 001st Prime"; }

    std::string solve() override {
      return std::to_string(nth_prime(10'001));
    }
};

const REGISTER_PROBLEM(7, P007);
