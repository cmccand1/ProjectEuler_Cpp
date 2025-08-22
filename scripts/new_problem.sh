#!/usr/bin/env bash
set -euo pipefail

# Determine repository root based on script location
script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
repo_root="$(cd "${script_dir}/.." && pwd)"
problems_root="${repo_root}/src/problems"

# Prompt for problem number
read -rp "Enter problem number (e.g., 1 or 001): " raw
if [[ -z "${raw:-}" || ! "$raw" =~ ^[0-9]+$ ]]; then
  echo "error: problem number must be a positive integer" >&2
  exit 1
fi
if (( 10#$raw < 1 )); then
  echo "error: problem number must be >= 1" >&2
  exit 1
fi
num=$(printf "%03d" "$raw")
# Decimal, no leading zeros for registration
num_dec=$((10#$raw))

# Prompt for problem name/title
read -rp "Enter problem name/title (e.g., Multiples of 3 or 5): " pname
if [[ -z "${pname//[[:space:]]/}" ]]; then
  echo "error: problem name must not be empty" >&2
  exit 1
fi
# Escape for C++ string literal
pname_escaped="${pname//\\/\\\\}"
pname_escaped="${pname_escaped//\"/\\\"}"

# Create directory and files
dir="${problems_root}/p${num}"
mkdir -p "$dir"
cat > "$dir/p${num}.cpp" <<EOF
#include "euler/problem.hpp"
#include <string>

class P${num} final : public IProblem {
public:
  [[nodiscard]] std::string name() const override { return "${pname_escaped}"; }
  [[nodiscard]] std::string solve() override {
    // TODO: implement
    return "TODO";
  }
};
const REGISTER_PROBLEM(${num_dec}, P${num});
EOF

# Store a literal CMake variable reference to avoid bash expansion under set -u
cmake_include_dir='${CMAKE_SOURCE_DIR}/include'

cat > "$dir/CMakeLists.txt" <<EOF
add_library(p${num} OBJECT p${num}.cpp)
target_include_directories(p${num} PRIVATE ${cmake_include_dir})
target_link_libraries(p${num} PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p${num}>)
EOF

echo "Created src/problems/p${num}/ (P${num} stub)."
