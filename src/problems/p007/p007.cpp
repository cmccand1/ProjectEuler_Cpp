#include <cassert>
#include <iostream>

#include "euler/problem.hpp"
#include <string>

#include "euler/util.hpp"

class P007 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override { return "10 001st Prime"; }

    [[nodiscard]] std::string solve() override {
      constexpr unsigned long long N = 10'001;
      return std::to_string(nth_prime(N));
    }
};

const REGISTER_PROBLEM (
7
,
P007
);