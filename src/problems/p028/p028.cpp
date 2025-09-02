#include <cassert>
#include <iomanip>
#include <iostream>

#include "euler/problem.hpp"
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

class P028 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Number Spiral Diagonals";
    }


    [[nodiscard]] std::string solve() override {
      constexpr std::size_t size = 1'001;
      const auto sum = computeDiagonalSum(size);
      return boost::multiprecision::to_string(sum);
    }

    // sum the diagonal of the generated 2d vector
    cpp_int computeDiagonalSumSlow(
      const std::vector<std::vector<std::size_t> > &grid) {
      cpp_int sum = 0;
      for (std::size_t i = 0; i < grid.size(); ++i) {
        sum += grid[i][i];
        sum += grid[(grid.size() - 1) - i][i];
      }
      return sum - 1; // double counted middle element
    }

    // only generate terms on the diagonal using a skip sequence
    cpp_int computeDiagonalSum(std::size_t size) {
      cpp_int sum = 1;
      const std::size_t stop = size * size;
      for (std::size_t term = 1, skip = 2; ; skip += 2) {
        for (std::size_t i = 0; i < 4; ++i) {
          term += skip;
          sum += term;
          if (term == stop) return sum;
        }
      }
    }

    // generate the entire 2d vector
    std::vector<std::vector<std::size_t> > generateSpiral(
      const std::size_t size) {
      assert(size > 0 && (size % 2 == 1));
      std::vector<std::vector<std::size_t> > grid(
        size,
        std::vector<std::size_t>(size));

      const std::size_t middle = size / 2;
      std::size_t x = middle; // row
      std::size_t y = middle; // col

      const std::size_t stop = size * size;
      std::size_t term = 1;
      grid[x][y] = term;

      // Directions: right, down, left, up
      static constexpr int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

      std::size_t stepLen = 1;
      while (term < stop) {
        for (int d = 0; d < 4 && term < stop; ++d) {
          const auto dx = dirs[d][0];
          const auto dy = dirs[d][1];
          const std::size_t moves = stepLen;
          for (std::size_t i = 0; i < moves && term < stop; ++i) {
            x = static_cast<std::size_t>(static_cast<int>(x) + dx);
            y = static_cast<std::size_t>(static_cast<int>(y) + dy);
            grid[x][y] = ++term;
          }
          if (d % 2 == 1) ++stepLen; // increase after completing two directions
        }
      }
      return grid;
    }

    void displaySpiral(const std::vector<std::vector<std::size_t> > &grid) {
      for (std::size_t i = 0; i < grid.size(); ++i) {
        for (std::size_t j = 0; j < grid[0].size(); ++j) {
          std::cout << std::setw(5) << grid[i][j];
          if (j == grid[0].size() - 1) {
            std::cout << "\n";
          } else {
            std::cout << " ";
          }
        }
      }
    }
};

const REGISTER_PROBLEM(28, P028);
