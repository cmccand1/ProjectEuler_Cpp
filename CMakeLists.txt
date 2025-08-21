# Top-level CMake for ProjectEuler_Cpp
#
# Overview
# - euler_common: Common utilities used by all problems.
# - Problems: Each problem (pNNN) is built as an OBJECT library in src/problems/pNNN
#   and appends its object files to a GLOBAL CMake property called PROBLEM_OBJECTS.
# - euler (executable): Links euler_common and all problem object files so that
#   each problem’s static Registrar runs and registers itself in the runtime registry.
#
# Why a GLOBAL property?
# Regular CMake variables do not naturally accumulate across nested add_subdirectory calls
# without careful PARENT_SCOPE plumbing and ordering. Each problem subdir does:
#   set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:pNNN>)
# Then, at the top-level, we gather them with get_property(... GLOBAL PROPERTY PROBLEM_OBJECTS)
# and pass them into the euler executable. This guarantees all problem objects are linked,
# ensuring their static registration code is emitted and executed at runtime.
#
# Adding a new problem
# - Create src/problems/pXYZ with pXYZ.cpp and a CMakeLists.txt that builds an OBJECT library
#   and appends $<TARGET_OBJECTS:pXYZ> to the GLOBAL PROBLEM_OBJECTS property (see p001 for reference).
# - Reconfigure and build; the problem will be linked into euler automatically and appear under
#   --list and run under --all.
#
# Notes
# - On macOS and Linux, the explicit whole-archive/force_load flags are unnecessary when using
#   object libraries with a forced inclusion pattern via GLOBAL property.
# - target_sources(euler PRIVATE ${PROBLEM_OBJECTS}) is kept for clarity; it is redundant given
#   the objects are already listed in add_executable, but harmless.

cmake_minimum_required(VERSION 3.23)
project(ProjectEuler_Cpp LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common code shared by all problems
add_library(euler_common STATIC
        src/common/util.cpp
)
# Public include path for headers under include/
target_include_directories(euler_common PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Boost for arbitrary precision (Boost.Multiprecision is header-only by default)
# Prefer imported targets; fall back to include dirs if older FindBoost is used.
find_package(Boost 1.70 REQUIRED)
if (TARGET Boost::boost)
    target_link_libraries(euler_common PUBLIC Boost::boost)
else()
    target_include_directories(euler_common PUBLIC ${Boost_INCLUDE_DIRS})
endif()

# Add all problems; each subdir appends its OBJECT library to the GLOBAL property
add_subdirectory(src/problems)

# Collect every problem’s object file(s) that were appended in subdirectories
get_property(PROBLEM_OBJECTS GLOBAL PROPERTY PROBLEM_OBJECTS)

# Main executable: include main and all problem objects so registration runs
add_executable(euler src/main.cpp ${PROBLEM_OBJECTS})
# Link common utilities
target_link_libraries(euler PRIVATE euler_common)
# Provide absolute path to answers.txt for the runtime check
target_compile_definitions(euler PRIVATE ANSWERS_TXT_PATH="${CMAKE_SOURCE_DIR}/answers.txt")

# Redundant but explicit: also add problem objects as sources
# (safe even if PROBLEM_OBJECTS is empty)
target_sources(euler PRIVATE ${PROBLEM_OBJECTS})
