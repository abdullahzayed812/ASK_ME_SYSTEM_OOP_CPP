#ifndef HELPER_H
#define HELPER_H 1

#include <string>
#include <vector>

class Helper {
 private:
  Helper();
  static Helper* helper;

 public:
  static Helper* createHelper();
  static void freeHelper();

  std::vector<std::string> readFileLines(const std::string&);
  void writeFileLines(const std::vector<std::string>&, const std::string&, bool append = true);
  std::vector<std::string> splitStringLine(const std::string&, const std::string& delimiter = ",");
};

#endif