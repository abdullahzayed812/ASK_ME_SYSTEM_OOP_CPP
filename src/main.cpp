
#include <iostream>
#include <vector>

#include "../include/helper.hpp"

std::vector<std::string> splitStringLine(const std::string& line,
                                         const std::string& delimiter = ",") {
  std::string copy = line;
  std::vector<std::string> result;

  int pos = 0;
  std::string substr;

  while ((pos = (int)copy.find(delimiter)) != -1) {
    substr = copy.substr(0, pos);
    result.push_back(substr);
    copy.erase(0, pos + delimiter.length());
  }

  return result;
}

int main() {
  Helper* helper = Helper::createHelper();

  std::vector<std::string> result = helper->splitStringLine(
      "211,-1,13,11,1,It was nice to chat to you,For my pleasure Dr Mostafa");

  std::vector<std::string>::iterator it;

  for (it = result.begin(); it != result.end(); it++) {
    std::cout << *it << "\t";
  }

  Helper::freeHelper();

  return 0;
}