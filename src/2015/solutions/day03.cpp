#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>

enum class Solutions { PartOne, PartTwo };

using spot = std::tuple<int, int, int, int>;

template <typename T>
int solve(T& is, Solutions s) {
  using char_iter = std::istreambuf_iterator<char>;

  if (s == Solutions::PartOne) {
    std::set<spot> spots_visited{};
    spots_visited.emplace(0, 0, 0, 0);
    spot current = {0, 0, 0, 0};

    for (char_iter it{is}; it != char_iter{}; ++it) {
      auto [n, s, e, w] = current;
      switch (*it) {
        case '^':  // North
          current = {++n, --s, e, w};
          spots_visited.emplace(current);
          break;
        case 'v':  // South
          current = {--n, ++s, e, w};
          spots_visited.emplace(current);
          break;
        case '>':  // East
          current = {n, s, ++e, --w};
          spots_visited.emplace(current);
          break;
        case '<':  // West
          current = {n, s, --e, ++w};
          spots_visited.emplace(current);
          break;
      }
    }

    return spots_visited.size();
  } else if (s == Solutions::PartTwo) {
    std::set<spot> spots_visited{};
    spots_visited.emplace(0, 0, 0, 0);
    spot santa = {0, 0, 0, 0};
    spot robot = {0, 0, 0, 0};
    spot* current = &santa;

    for (char_iter it{is}; it != char_iter{};
         ++it, (*current == santa ? current = &robot : current = &santa)) {
      auto [n, s, e, w] = *current;
      switch (*it) {
        case '^':  // North
          *current = {++n, --s, e, w};
          spots_visited.emplace(*current);
          break;
        case 'v':  // South
          *current = {--n, ++s, e, w};
          spots_visited.emplace(*current);
          break;
        case '>':  // East
          *current = {n, s, ++e, --w};
          spots_visited.emplace(*current);
          break;
        case '<':  // West
          *current = {n, s, --e, ++w};
          spots_visited.emplace(*current);
          break;
      }
    }

    return spots_visited.size();
  }

  throw std::runtime_error("Solving the wrong problem!");
}

void solve_part_1() {
  std::map<std::string, int> cases = {{">", 2}, {"^>v<", 4}, {"^v^v^v^v^v", 2}};
  for (const auto& [case_str, expected] : cases) {
    std::stringstream ss{case_str};
    if (auto got = solve(ss, Solutions::PartOne); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day03.txt"};
  assert(ifs.is_open());

  int count = solve(ifs, Solutions::PartOne);
  std::cout << "Part One Solution: " << count << std::endl;
}

void solve_part_2() {
  std::map<std::string, int> cases = {{"^v", 3}, {"^>v<", 3}, {"^v^v^v^v^v", 11}};
  for (const auto& [case_str, expected] : cases) {
    std::stringstream ss{case_str};
    if (auto got = solve(ss, Solutions::PartTwo); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day03.txt"};
  assert(ifs.is_open());

  int count = solve(ifs, Solutions::PartTwo);
  std::cout << "Part One Solution: " << count << std::endl;
}

int main() {
  solve_part_1();
  solve_part_2();
  return 0;
}
