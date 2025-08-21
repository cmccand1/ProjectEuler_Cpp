#include "euler/problem.hpp"
#include <string>

class P005 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Smallest Multiple";
    }

    std::string solve() override {
      int candidate = 40; // start at first multiple of 20
      bool found = false;
      while (!found) {
        // check for divisibility by each number in the range [1, 20], skipping
        // a few already known divisors and skipping by multiples of 20
        for (int i = 19; i >= 3; --i) {
          if (candidate)
            if (candidate % i != 0) {
              candidate += 20;
              break;
            }
          if (i == 3) {
            found = true;
          }
        }
      }

      return std::to_string(candidate);
    }
};

const REGISTER_PROBLEM(5, P005);
