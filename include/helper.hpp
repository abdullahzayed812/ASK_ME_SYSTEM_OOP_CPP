#ifndef HELPER_H
#define HELPER_H 1

#include <cstring>
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
};

#endif