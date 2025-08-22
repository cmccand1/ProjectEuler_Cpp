#pragma once

#include <cassert>
#include <numbers>
#include <vector>
#include <cmath>
#include <concepts>
#include <type_traits>
#include <boost/multiprecision/cpp_int.hpp>
#include <__ranges/reverse_view.h>

/**
 * The sieve of eratosthenes is a list of all the primes ≤ n.
 *
 * @param n the upper bound of the sieve
* @return a boolean array where true means the integer represented by
 * the index is prime and false means it is composite
 */
[[nodiscard]] std::vector<bool> sieve_of_eratosthenes(unsigned int n);

/**
 * Finds the sum of the digits of an arbitrarily large integer
 * (limited only by the available system memory)
 * @param n the integer whose digit sum will be found
 * @return the digit sum as an arbitrarily large integer
 */
[[nodiscard]] inline boost::multiprecision::cpp_int digit_sum(
  boost::multiprecision::cpp_int n) {
  boost::multiprecision::cpp_int sum = 0;
  n = boost::multiprecision::abs(n);
  while (n) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

/**
 * You already know...
 */
[[nodiscard]] inline boost::multiprecision::cpp_int factorial(int n) {
  assert(n > 0);
  boost::multiprecision::cpp_int res = 1;
  for (int i = 2; i <= n; i++) {
    res *= i;
  }
  return res;
};

/**
 * Calculate the nth prime number
 * @param n the index of the prime number to find
 * @return the nth prime number
 */
[[nodiscard]] unsigned long long nth_prime(std::size_t n);

/**
 * Find the nth Fibonacci number.
 *
 * This fib implementation uses the Binet formula with rounding.
 * It’s fine for small n, but floating-point precision won’t hold for very large n.
 * @param n the index of the fibonacci number to find
 * @return the nth fibonacci number
 */
[[nodiscard]] inline long long fib(long long n) {
  assert(n >= 0);
  constexpr auto phi = std::numbers::phi_v<long double>;
  const auto result = std::llround(
    std::pow(phi, static_cast<long double>(n)) / std::sqrt(5.0L));
  return result;
}

/**
 * Calculate the index of a Fibonacci number
 * @param fib the Fibonacci number whose index to find
 * @return the index of fib
 */
[[nodiscard]] inline long long inverse_fib(long long fib) {
  assert(fib >= 1);
  constexpr auto phi = std::numbers::phi_v<long double>;
  // calculate the log (base phi) of sqrt(5)*fib using a change of base
  const auto val = std::sqrt(5.0L) * static_cast<long double>(fib);
  const auto n = std::llround(std::log(val) / std::log(phi));
  // change of log base
  return n;
}

/**
 * Calculates the sum of the first n natural numbers
 * @param n the numbers of natural numbers to sum
 * @return the sum
 */
[[nodiscard]] inline unsigned long natural_sum(std::size_t n) {
  return n * (n + 1) / 2;
}

/**
 * Return the sum of the squares of the first n numbers
 * @param n how many numbers
 * @return the sum of squares
 */
[[nodiscard]] inline unsigned long sum_of_squares(std::size_t n) {
  return (n * (n + 1) * (2 * n + 1)) / 6;
}

/**
 * Determines whether a given integer n is prime
 * @param n the integer to check
 * @return true if prime, false otherwise
 */
[[nodiscard]] inline bool is_prime(std::size_t n) noexcept {
  if (n < 2) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  const auto sqrt_n = static_cast<std::size_t>(std::sqrt(n));
  for (std::size_t i = 3; i < sqrt_n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}


/**
 * Determine whether a number is a palindrome number (e.g. 11122111, 12321, 22, 5, etc.)
 * @tparam T a std::integral type
 * @param x the number to check
 * @return true if x is a palindrome number, false if not
 */
template<std::integral T>
[[nodiscard]] constexpr bool is_palindrome_fast(T x) noexcept {
  // Negative (for signed types) cannot be a base-10 palindrome.
  if constexpr (std::signed_integral<T>) {
    if (x < 0) return false;
  }

  using U = std::make_unsigned_t<T>;
  U ux = static_cast<U>(x);

  // Numbers ending with 0 (but not 0 itself) are not palindromes: e.g., 10, 100.
  if (ux != 0 && ux % 10 == 0) return false;

  U rev = 0; // reverse of the *second half* of the digits
  // Build 'rev' until it has at least as many digits as the remaining 'ux'.
  while (ux > rev) {
    rev = rev * 10 + (ux % 10);
    ux /= 10;
  }

  // For even digits: ux == rev
  // For odd digits:  ux == rev/10 (middle digit is ignored)
  return ux == rev || ux == (rev / 10);
}

template<std::integral T>
[[nodiscard]] constexpr bool is_palindrome_slow(T x) noexcept {
  // Negative numbers aren't palindromes in base-10
  if constexpr (std::signed_integral<T>) {
    if (x < 0) return false;
  }
  // Convert to string once, then compare with its reverse view
  std::string s = std::to_string(static_cast<unsigned long long>(x));
  return std::ranges::equal(s, std::ranges::views::reverse(s));
}
