#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cctype>
#include <cassert>
#include "euler/problem.hpp"

// Load answers.txt once and cache it for lookups
static std::unordered_map<int, std::string> load_answers() {
  std::unordered_map<int, std::string> out;
#ifdef ANSWERS_TXT_PATH
  std::ifstream in(ANSWERS_TXT_PATH);
  if (!in) return out;
  std::string line;
  while (std::getline(in, line)) {
    // trim
    auto l = line;
    auto ltrim = [](std::string &s) {
      size_t i = 0;
      while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i])))
        ++
            i;
      s.erase(0, i);
    };
    auto rtrim = [](std::string &s) {
      size_t i = s.size();
      while (i > 0 && std::isspace(static_cast<unsigned char>(s[i - 1]))) --i;
      s.erase(i);
    };
    ltrim(l);
    rtrim(l);
    if (l.empty()) continue;
    auto dot = l.find('.');
    if (dot == std::string::npos) continue;
    std::string id_str = l.substr(0, dot);
    rtrim(id_str);
    // simple digits check
    bool ok = !id_str.empty();
    for (char c : id_str)
      if (!std::isdigit(static_cast<unsigned char>(c))) {
        ok = false;
        break;
      }
    if (!ok) continue;
    int id = 0;
    try { id = std::stoi(id_str); } catch (...) { continue; }
    std::string rest = l.substr(dot + 1);
    ltrim(rest);
    rtrim(rest);
    // rest may be empty if answer unknown; store as empty string
    out[id] = rest;
  }
#endif
  return out;
}

static const std::unordered_map<int, std::string> &answers_map() {
  static const std::unordered_map<int, std::string> cache = load_answers();
  return cache;
}

static void run_one(const int id) {
  const auto prob = ProblemRegistry::instance().make(id);
  if (!prob) {
    std::cerr << "Problem " << id << " not found.\n";
    return;
  }
  const auto start = std::chrono::steady_clock::now();
  const auto ans = prob->solve();
  const auto end = std::chrono::steady_clock::now();
  const std::chrono::duration<double, std::milli> ms = end - start;

  // Compare against expected if available and non-empty
  std::string note;
  if (const auto it = answers_map().find(id); it != answers_map().end()) {
    const std::string &expected = it->second; // may be empty if unknown
    if (!expected.empty()) {
      if (ans == expected) {
        note = " [OK]";
      } else {
        std::cerr << "Incorrect answer for Problem " << id << " (" << prob->name()
                  << ")\n  expected: '" << expected << "'\n  got:      '" << ans << "'\n";
        assert((ans == expected) && "Incorrect Project Euler answer");
      }
    }
  }

  std::cout << "P" << id << " - " << prob->name() << " => " << ans
      << note << " (" << ms.count() << " ms)\n";
}

int main(const int argc, char **argv) {
  if (argc == 1) {
    std::cout << "Usage: euler <problem-id>|--all|--list\n";
    return 0;
  }
  const std::string arg = argv[1];
  if (arg == "--list") {
    for (const auto id : ProblemRegistry::instance().ids())
      std::cout << id << "\n";
    return 0;
  }
  if (arg == "--all") {
    for (const auto id : ProblemRegistry::instance().ids()) run_one(id);
    return 0;
  }
  try {
    run_one(std::stoi(arg));
  } catch (const std::exception& e) {
    std::cerr << "Error parsing problem id '" << arg << "': " << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "Unknown error parsing problem id: " << arg << "\n";
    return 1;
  }
  return 0;
}
