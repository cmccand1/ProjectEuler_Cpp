#include <cassert>

#include "euler/problem.hpp"
#include <string>

class P003 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Largest Prime Factor";
    }

    std::string solve() override {
      const long long largestPrime = largestPrimeFactor(600'851'475'143);
      return std::to_string(largestPrime);
    }

    /**
     * Finds the largest prime factor of a given positive integer n
     * @param n a positive integer
     * @return the largest prime factor of n
     */
    static long long largestPrimeFactor(long long n) {
      if (n < 0) {
        throw std::invalid_argument(
          "Invalid argument " + std::to_string(n) +
          ". Must be a positive integer.");
      }
      long long largestPrime = -1;

      // handle factors of 2
      while (n % 2 == 0) {
        largestPrime = 2;
        n /= 2;
      }

      // Handle odd factors starting from 3
      // Iterate only up to the square root of n
      int i = 3;
      while (i * i <= n) {
        while (n % i == 0) {
          largestPrime = i;
          n /= i;
        }
        i += 2;
      }

      // remaining n is a prime factor
      if (n > 2) largestPrime = n;

      return largestPrime;
    }
};

const REGISTER_PROBLEM(003, P003);
