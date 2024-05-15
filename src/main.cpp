
#include <iostream>
#include <vector>

#include "../include/helper.hpp"
#include "../include/question.hpp"

int main() {
  std::vector<std::string> lines = Helper::readFileLines("database/questions.txt");

  for (auto line : lines) {
    std::cout << line << "\n";
  }
  return 0;
}