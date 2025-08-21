// #ifndef PROJECTEULER_CPP_PROBLEM_HPP
// #define PROJECTEULER_CPP_PROBLEM_HPP
//
// #endif //PROJECTEULER_CPP_PROBLEM_HPP

#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ranges>

// This is the Strategy pattern (each IProblem is a strategy for producing an
// answer) plus a lightweight Factory Method/Registry to construct a problem by number.

/**
 * Interface for all Project Euler problem implementations.
 * Each problem is a strategy that can produce a string answer.
 */
struct IProblem {
  virtual ~IProblem() = default;

  [[nodiscard]] virtual std::string name() const = 0;

  // Return the final answer as a string; print/log timing elsewhere.
  virtual std::string solve() = 0;
};

/**
 * Registry for Project Euler problem implementations.
 * Uses the Singleton pattern to maintain a global registry of problem factories.
 */
class ProblemRegistry {
  public:
    using Factory = std::function<std::unique_ptr<IProblem>()>;

    static ProblemRegistry &instance() {
      static ProblemRegistry inst;
      return inst;
    }

    void add(const int id, Factory f) { factories_[id] = std::move(f); }

    [[nodiscard]] std::unique_ptr<IProblem> make(const int id) const {
      if (const auto it = factories_.find(id); it != factories_.end()) {
        return (it->second)();
      }
      return nullptr;
    }

    [[nodiscard]] std::vector<int> ids() const {
      std::vector<int> out;
      out.reserve(factories_.size());
      for (const auto &key : factories_ | std::views::keys) out.push_back(key);
      std::ranges::sort(out);
      return out;
    }

  private:
    std::unordered_map<int, Factory> factories_;
};

struct Registrar {
  Registrar(const int id, ProblemRegistry::Factory f) {
    ProblemRegistry::instance().add(id, std::move(f));
  }
};

#define REGISTER_PROBLEM(ID, TYPE) \
static ::Registrar _registrar_##TYPE( (ID), [](){ return std::make_unique<TYPE>(); } )
