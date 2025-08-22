#include <cassert>
#include <string>
#include <unordered_map>

#include "euler/problem.hpp"

class NumberStringBuilder {
  private:
    std::string number_string{};
    int thousands_{0}, hundreds_{0}, tens_{0}, ones_{0};

    std::unordered_map<int, std::string> ones_map{
      {1, "one"},
      {2, "two"},
      {3, "three"},
      {4, "four"},
      {5, "five"},
      {6, "six"},
      {7, "seven"},
      {8, "eight"},
      {9, "nine"},
    };
    std::unordered_map<int, std::string> tens_map{
      {10, "ten"},
      {11, "eleven"},
      {12, "twelve"},
      {13, "thirteen"},
      {14, "fourteen"},
      {15, "fifteen"},
      {16, "sixteen"},
      {17, "seventeen"},
      {18, "eighteen"},
      {19, "nineteen"},
      {20, "twenty"},
      {30, "thirty"},
      {40, "forty"},
      {50, "fifty"},
      {60, "sixty"},
      {70, "seventy"},
      {80, "eighty"},
      {90, "ninety"},
    };

  public:
    NumberStringBuilder() = default;

    /**
     * Construct the word string representation of this number.
     * E.g., "one hundred and twenty-one".
     *
     * The current implementation doesn't include any spaces in the final result.
     * @param n the integer to construct as a word string
     */
    explicit NumberStringBuilder(int n) {
      assert(0 < n && n <= 1000);
      this->ones_ = n % 10;
      n /= 10;
      this->tens_ = n % 10;
      n /= 10;
      this->hundreds_ = n % 10;
      n /= 10;
      this->thousands_ = n % 10;

      // thousands
      if (thousands_ != 0) {
        number_string += ones_map[thousands_] + "thousand";
      }
      // hundreds
      if (hundreds_ != 0) {
        number_string += ones_map[hundreds_] + "hundred";
      }
      // and
      if ((hundreds_ != 0 || thousands_ != 0) && (tens_ != 0 || ones_ != 0)) {
        number_string += "and";
      }
      // tens
      if (tens_ != 0) {
        // special cases for 11, 12, 13, etc.
        const auto it = tens_map.find(tens_ * 10 + ones_);
        if (it != tens_map.end()) {
          number_string += tens_map[tens_ * 10 + ones_];
          return;
        }
        // write the tens place and the ones place
        number_string += tens_map[tens_ * 10] + ones_map[ones_];
        return;
      }

      // ones
      number_string += ones_map[ones_];
    };

    [[nodiscard]] size_t length() const {
      return number_string.size();
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const NumberStringBuilder &obj) {
      os << obj.number_string;
      return os;
    }
};

class P017 final : public IProblem {
  public:
    [[nodiscard]] std::string name() const override {
      return "Number Letter Counts";
    }

    [[nodiscard]] std::string solve() override {
      size_t count = 0;
      for (int i = 1; i <= 1000; ++i) {
        count += NumberStringBuilder(i).length();
      }
      return std::to_string(count);
    }
};


const REGISTER_PROBLEM (
17
,
P017
);