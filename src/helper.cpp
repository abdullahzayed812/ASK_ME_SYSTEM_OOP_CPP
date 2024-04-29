#include "../include/helper.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

Helper* Helper::helper = nullptr;

Helper::Helper() {}

Helper* Helper::createHelper() {
  if (Helper::helper == nullptr) {
    std::cout << "Create new instance from helper class\n";

    Helper::helper = new Helper();
  }

  return Helper::helper;
}

void Helper::freeHelper() {
  if (Helper::helper != nullptr) {
    delete Helper::helper;
    Helper::helper = nullptr;
  } else {
    std::cout << "Helper already freed\n";
  }
}

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