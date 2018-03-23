#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

enum class Solutions { PartOne, PartTwo };

template <typename T>
int solve(T& is, Solutions s) {
  if (s == Solutions::PartOne) {
    int l, w, h;
    char separator;
    if (!(is >> l >> separator >> w >> separator >> h)) {
      throw std::runtime_error("Wrong input.");
    }

    int lw_area = l * w;
    int wh_area = w * h;
    int hl_area = h * l;
    int min_area = std::min({lw_area, wh_area, hl_area});
    return 2 * lw_area + 2 * wh_area + 2 * hl_area + min_area;
  } else if (s == Solutions::PartTwo) {
    int l, w, h;
    char separator;
    if (!(is >> l >> separator >> w >> separator >> h)) {
      throw std::runtime_error("Wrong input.");
    }

    int lw_perimeter = 2 * (l + w);
    int wh_perimeter = 2 * (w + h);
    int hl_perimeter = 2 * (h + l);
    int min_perimeter = std::min({lw_perimeter, wh_perimeter, hl_perimeter});
    int cubic_feet = l * w * h;

    return min_perimeter + cubic_feet;
  }

  throw std::runtime_error("Solving the wrong problem!");
}

void solve_part_1() {
  std::map<std::string, int> cases = {{"2x3x4", 58}, {"1x1x10", 43}};
  for (const auto& [case_str, expected] : cases) {
    std::stringstream ss{case_str};
    if (auto got = solve(ss, Solutions::PartOne); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day02.txt"};
  assert(ifs.is_open());

  std::string line;
  int result = 0;
  while (std::getline(ifs, line)) {
    std::istringstream iss{line};
    result += solve(iss, Solutions::PartOne);
  }

  std::cout << "Part One Solution: " << result << std::endl;
}

void solve_part_2() {
  std::map<std::string, int> cases = {{"2x3x4", 34}, {"1x1x10", 14}};
  for (const auto& [case_str, expected] : cases) {
    std::stringstream ss{case_str};
    if (auto got = solve(ss, Solutions::PartTwo); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day02.txt"};
  assert(ifs.is_open());

  std::string line;
  int result = 0;
  while (std::getline(ifs, line)) {
    std::istringstream iss{line};
    result += solve(iss, Solutions::PartTwo);
  }

  std::cout << "Part Two Solution: " << result << std::endl;
}

int main() {
  solve_part_1();
  solve_part_2();
  return 0;
}
