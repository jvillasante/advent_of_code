#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

enum class Solutions { PartOne, PartTwo };

template <typename T>
int solve(T& is, Solutions s) {
  using char_iter = std::istreambuf_iterator<char>;

  if (s == Solutions::PartOne) {
    int count{0};
    for (char_iter it{is}; it != char_iter{}; ++it) {
      if (*it == '(') {
        ++count;
      } else if (*it == ')') {
        --count;
      }
    }

    return count;
  } else if (s == Solutions::PartTwo) {
    int count{0}, index{1};
    for (char_iter it{is}; it != char_iter{}; ++it, ++index) {
      if (*it == '(') {
        ++count;
      } else if (*it == ')') {
        --count;
      }

      if (count < 0) {
        break;
      }
    }

    return index;
  }

  throw std::runtime_error("Solving the wrong problem!");
}

void solve_part_1() {
  std::map<std::string, int> cases = {{"(())", 0}, {"()()", 0}, {"(((", 3},  {"(()(()(", 3}, {"))(((((", 3},
                                      {"())", -1}, {"))(", -1}, {")))", -3}, {")())())", -3}};
  for (const auto& [case_str, expected] : cases) {
    std::stringstream ss{case_str};
    if (auto got = solve(ss, Solutions::PartOne); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day01.txt"};
  assert(ifs.is_open());

  int count = solve(ifs, Solutions::PartOne);
  std::cout << "Part One Solution: " << count << std::endl;
}

void solve_part_2() {
  std::map<std::string, int> cases = {{")", 1}, {"()())", 5}};
  for (const auto& [case_str, expected] : cases) {
    std::stringstream ss{case_str};
    if (auto got = solve(ss, Solutions::PartTwo); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day01.txt"};
  assert(ifs.is_open());

  int index = solve(ifs, Solutions::PartTwo);
  std::cout << "Part Two Solution: " << index << std::endl;
}

int main() {
  solve_part_1();
  solve_part_2();
  return 0;
}
