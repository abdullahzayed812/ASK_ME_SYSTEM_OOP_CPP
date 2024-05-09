#include "../include/helper.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Helper::Helper() {}

std::vector<std::string> Helper::readFileLines(const std::string& path) {
  std::vector<std::string> lines;

  std::fstream fileHandler(path);

  if (fileHandler.fail()) {
    std::cout << "\n\nERROR: Can't open the file\n\n";
    return lines;
  }

  std::string line;

  while (getline(fileHandler, line)) {
    if (line.size() == 0) {
      continue;
    }

    lines.push_back(line);
  }

  fileHandler.close();

  return lines;
}

void Helper::writeFileLines(const std::vector<std::string>& lines, const std::string& filePath,
                            bool append) {
  auto status = std::ios::in | std::ios::out | std::ios::app;

  if (!append) {
    status = std::ios::in | std::ios::out | std::ios::trunc;
  }

  std::fstream fileHandler(filePath, status);

  if (fileHandler.fail()) {
    std::cout << "\n\nERROR: Can't open the file\n\n";
    return;
  }

  for (const std::string& line : lines) {
    fileHandler << line << "\n";
  }

  fileHandler.close();
}

std::vector<std::string> Helper::splitStringLine(const std::string& line,
                                                 const std::string& delimiter) {
  std::string copy = line;
  std::vector<std::string> result;

  int pos = 0;
  std::string substr;

  while ((pos = (int)copy.find(delimiter)) != -1) {
    substr = copy.substr(0, pos);
    result.push_back(substr);
    copy.erase(0, pos + delimiter.length());
  }

  result.push_back(copy);
  return result;
}

int Helper::toInt(const std::string& str) {
  std::istringstream iss(str);

  int num;
  iss >> num;

  return num;
}

int Helper::readInt(const int& min, const int& max) {
  std::cout << "\nEnter number in range " << min << " - " << max << ": ";

  int value;
  std::cin >> value;

  while (value < min || value > max) {
    std::cout << "\n\nERROR: Out of range... Try again.\n";
    std::cout << "\nEnter number in range " << min << " - " << max << ": ";

    std::cin >> value;
  }

  return value;
}

int Helper::showReadMenu(const std::vector<std::string>& choices) {
  std::cout << "\nMenu:\n";

  for (std::size_t i = 0; i < choices.size(); i++) {
    std::cout << "\t" << i + 1 << ": " << choices[i] << "\n";
  }

  return Helper::readInt(1, choices.size());
}