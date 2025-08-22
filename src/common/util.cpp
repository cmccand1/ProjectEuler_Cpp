#include "euler/util.hpp"

std::vector<bool> sieve_of_eratosthenes(unsigned int n) {
  assert(n > 0);
  const auto size = static_cast<std::vector<bool>::size_type>(n + 1);
  std::vector<bool> is_prime(size, true);
  is_prime[0] = is_prime[1] = false;
  for (std::size_t i = 2; i * i <= n; ++i) {
    if (is_prime[i])
      for (std::size_t j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
  }
  return is_prime;
}

unsigned long long nth_prime(std::size_t n) {
  assert(n > 0);
  if (n == 1) return 2;

  // Rosser's Theorem for estimate
  const auto estimatedbl = (n >= 6)
                             ? (n * (std::log(n) + std::log(std::log(n))))
                             : 15;
  const auto estimate = static_cast<unsigned int>(std::round(estimatedbl));

  const auto sieve = sieve_of_eratosthenes(estimate + 1);

  // count until we find the nth prime
  std::size_t count = 1;
  for (size_t i = 3; count < n; i += 2) {
    if (sieve[i]) ++count;
    if (count == n) {
      return i;
    }
  }
  throw std::runtime_error("");
}
