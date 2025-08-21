#include "euler/util.hpp"
#include <string>

std::vector<bool> sieve_of_eratosthenes(int n) {
  assert(n > 0);
  std::vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= n; ++i) {
    if (is_prime[i])
      for (int j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
  }
  return is_prime;
}

long long nth_prime(int n) {
  assert(n > 0);
  if (n == 1) return 2;

  // Rosser's Theorem for estimate
  const long estimate = (n >= 6)
                               ? (n * (std::log(n) + std::log(std::log(n))))
                               : 15;

  auto sieve = sieve_of_eratosthenes(estimate + 1);

  // count until we find the nth prime
  long count = 1;
  for (size_t i = 3; count < n; i += 2) {
    if (sieve[i]) ++count;
    if (count == n) {
      return i;
    }
  }
  throw std::runtime_error("Failed to find the " + std::to_string(n) + "-th prime with current estimate");
}
