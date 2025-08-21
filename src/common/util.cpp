#include "euler/util.hpp"
#include <string>
#include <cmath>

std::vector<bool> sieve_of_eratosthenes(int n) {
  assert(n > 0);
  const auto size = static_cast<std::vector<bool>::size_type>(n + 1);
  std::vector<bool> is_prime(size, true);
  is_prime[0] = is_prime[1] = false;
  
  for (int i = 2; i * i <= n; ++i) {
    if (is_prime[static_cast<std::vector<bool>::size_type>(i)]) {
      for (int j = i * i; j <= n; j += i) {
        is_prime[static_cast<std::vector<bool>::size_type>(j)] = false;
      }
    }
  }
  return is_prime;
}

long long nth_prime(int n) {
  assert(n > 0);
  if (n == 1) return 2;

  // Rosser's Theorem for estimate
  const auto estimate_dbl = (n >= 6)
                               ? (n * (std::log(n) + std::log(std::log(n))))
                               : 15.0;
  const auto estimate = static_cast<int>(std::ceil(estimate_dbl));

  auto sieve = sieve_of_eratosthenes(estimate + 1);

  // count until we find the nth prime
  int count = 1;
  for (std::size_t i = 3; count < n; i += 2) {
    if (i >= sieve.size()) {
      throw std::runtime_error("Sieve size exceeded while searching for " + std::to_string(n) + "-th prime");
    }
    if (sieve[i]) ++count;
    if (count == n) {
      return static_cast<long long>(i);
    }
  }
  throw std::runtime_error("Failed to find the " + std::to_string(n) + "-th prime with current estimate");
}
