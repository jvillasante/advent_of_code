#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>

enum class Solutions { PartOne, PartTwo };

bool contains_bad_characters(const std::string& str) {
  return str.find("ab") != std::string::npos || str.find("cd") != std::string::npos ||
         str.find("pq") != std::string::npos || str.find("xy") != std::string::npos;
}

bool contains_duplicate_letter(const std::string& str) {
  for (auto i = 0u; i < str.size() - 1; ++i) {
    if (str[i] == str[i + 1]) {
      return true;
    }
  }

  return false;
}

bool contains_at_least_three_vowels(const std::string& str) {
  return std::count_if(std::begin(str), std::end(str), [](const char& ch) {
           return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
         }) >= 3;
}

bool solve(const std::string& str, Solutions s) {
  if (s == Solutions::PartOne) {
    std::regex vowels("([aeiou])\\w*([aeiou])\\w*([aeiou])");
    std::regex duplicates("(\\w)\\1+");
    std::regex banned("(ab)|(cd)|(pq)|(xy)");

    return !std::regex_search(str, banned) && std::regex_search(str, vowels) &&
           std::regex_search(str, duplicates);
  } else if (s == Solutions::PartTwo) {
    std::regex duplicate_non_overlap("(\\w)(\\w)(\\w*)\\1\\2+");
    std::regex repeat_with_gap("(\\w)(\\w)\\1+");

    return std::regex_search(str, duplicate_non_overlap) && std::regex_search(str, repeat_with_gap);
  }

  throw std::runtime_error("Solving the wrong problem!");
}

void solve_part_1() {
  std::map<std::string, bool> cases = {{"ugknbfddgicrmopn", true},
                                       {"aaa", true},
                                       {"jchzalrnumimnmhp", false},
                                       {"haegwjzuvuyypxyu", false},
                                       {"dvszwmarrgswjxmb", false}};
  for (const auto& [case_str, expected] : cases) {
    if (auto got = solve(case_str, Solutions::PartOne); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day05.txt"};
  assert(ifs.is_open());

  std::string line;
  int result = 0;
  while (std::getline(ifs, line)) {
    if (solve(line, Solutions::PartOne)) {
      ++result;
    }
  }

  std::cout << "Part One Solution: " << result << std::endl;
}

void solve_part_2() {
  std::map<std::string, bool> cases = {
      {"qjhvhtzxzqqjkmpb", true}, {"xxyxx", true}, {"uurcxstgmygtbstg", false}, {"ieodomkazucvgmuy", false}};
  for (const auto& [case_str, expected] : cases) {
    if (auto got = solve(case_str, Solutions::PartTwo); got != expected) {
      std::cout << "Test failed for input " << case_str << std::endl;
      std::cout << "  Expected: " << expected << std::endl;
      std::cout << "  Got: " << got << std::endl;
    }
  }

  std::ifstream ifs{"inputs/day05.txt"};
  assert(ifs.is_open());

  std::string line;
  int result = 0;
  while (std::getline(ifs, line)) {
    if (solve(line, Solutions::PartTwo)) {
      ++result;
    }
  }

  std::cout << "Part Two Solution: " << result << std::endl;
}

int main() {
  solve_part_1();
  solve_part_2();
  return 0;
}
