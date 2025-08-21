How this project is structured:
```
euler-cpp/
├─ CMakeLists.txt
├─ CMakePresets.json                # optional but handy
├─ include/
│  └─ euler/
│     ├─ problem.hpp                # interface + registry (Strategy + Factory Method)
│     └─ util.hpp                   # common helpers (gcd, sieve, etc.)
├─ src/
│  ├─ main.cpp                      # CLI runner (run one or all problems)
│  ├─ common/
│  │  └─ util.cpp
│  └─ problems/
│     ├─ CMakeLists.txt             # adds each pNNN subdir
│     ├─ p001/
│     │  ├─ CMakeLists.txt
│     │  └─ p001.cpp
│     └─ p002/
│        ├─ CMakeLists.txt
│        └─ p002.cpp
├─ tests/
│  ├─ CMakeLists.txt
│  └─ p001_test.cpp
├─ benchmarks/                      # (optional) google-benchmark
├─ data/                            # (optional) inputs for some problems
├─ scripts/
│  └─ new_problem.sh                # scaffolds a new pNNN
├─ .clang-format
├─ .clang-tidy
└─ README.md
```

Each problem sits in src/problems/pNNN (zero-padded width 3) and compiles as a tiny object library.

A single euler runner links all problem objects and picks which Strategy (problem) to run at runtime via a Registry + Factory Method.

Shared math goes in euler_common, so you don’t duplicate sieves, prime tests, big-int adapters, etc.

Unit tests live beside (but separate from) sources.

Each problem subdir adds an object library and bubbles its objects up

To make new problem script executable: chmod +x scripts/new_problem.sh

- Workflow
    - Add a new solution: `./scripts/new_problem.sh 42` → edit `src/problems/p042/p042.cpp.`
    - Build: `cmake -S . -B build && cmake --build build -j`.
    - Run one: `./build/euler 42`.
    - List: `./build/euler --list`.
    - Run all: `./build/euler --all`.
    - Tests: `ctest --test-dir build`.