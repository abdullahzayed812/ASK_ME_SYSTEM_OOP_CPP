
#include <iostream>

#include "../include/helper.hpp"

int main() {
  const std::string filePath = "questions.txt";

  Helper* helper = Helper::createHelper();

  std::vector<std::string> lines = helper->readFileLines(filePath);

  for (const std::string& line : lines) {
    std::cout << line << "\n";
  }

  helper->writeFileLines(lines, "test.txt");

  Helper::freeHelper();

  return 0;
}