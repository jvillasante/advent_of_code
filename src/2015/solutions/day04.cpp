#include "../common/md5.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

enum class Solutions { PartOne, PartTwo };

int solve(const std::string& str, Solutions s) {
  if (s == Solutions::PartOne) {
    for (uint64_t count = 0;; ++count) {
      auto result = MD5(str + std::to_string(count)).hexdigest();
      if (auto index = result.find("00000"); index == 0) {
        return count;
      }
    }
  } else if (s == Solutions::PartTwo) {
    for (uint64_t count = 0;; ++count) {
      auto result = MD5(str + std::to_string(count)).hexdigest();
      if (auto index = result.find("000000"); index == 0) {
        return count;
      }
    }
  }

  throw std::runtime_error("Solving the wrong problem!");
}

void solve_part_1() {
  std::map<std::string, int> cases = {{"abcdef", 609043}, {"pqrstuv", 1048970}};
  for (const auto& [case_str, expected] : cases) {
    if (auto got = solve(case_str, Solutions::PartOne); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day04.txt"};
  assert(ifs.is_open());

  std::string line;
  int result = 0;
  while (std::getline(ifs, line)) {
    result += solve(line, Solutions::PartOne);
  }

  std::cout << "Part One Solution: " << result << std::endl;
}

void solve_part_2() {
  std::ifstream ifs{"inputs/day04.txt"};
  assert(ifs.is_open());

  std::string line;
  int result = 0;
  while (std::getline(ifs, line)) {
    result += solve(line, Solutions::PartTwo);
  }

  std::cout << "Part Two Solution: " << result << std::endl;
}

int main() {
  solve_part_1();
  solve_part_2();
  return 0;
}
