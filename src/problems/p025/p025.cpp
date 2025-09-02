#include "euler/problem.hpp"
#include <string>

#include "euler/util.hpp"

class P025 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "1000-digit Fibonacci Number";
    }


    // find the index of the first fibonacci number with 1000 digits
    [[nodiscard]] std::string solve() override {
      // return brute_force();
      return binary_fib();
    }

    std::string binary_fib() {
      constexpr std::size_t target_len = 1'000;
      std::size_t prev_index = 1, curr_index = 2;

      // find an upper and lower bound
      while (digit_count(big_fib(curr_index)) < target_len) {
        prev_index = curr_index;
        curr_index *= 2;
      }

      // binary search within the bounds to find the answer
      while (prev_index <= curr_index) {
        std::size_t mid = prev_index + (curr_index - prev_index) / 2;
        std::size_t mid_len = digit_count(big_fib(mid));
        if (target_len < mid_len) {
          curr_index = mid - 1;
        } else if (target_len > mid_len) {
          prev_index = mid + 1;
        } else {
          // scan left until we find the first occurrence
          while (digit_count(big_fib(mid)) == target_len) {
            --mid;
          }
          return std::to_string(mid + 1);
        }
      }
      return "-1";
    }

    [[nodiscard]] std::string brute_force() {
      std::size_t i = 1;
      while (true) {
        if (cpp_int f_i = big_fib(i); digit_count(f_i) == 1'000) {
          break;
        }
        ++i;
      }
      return std::to_string(i);
    }
};

const REGISTER_PROBLEM(25, P025);
