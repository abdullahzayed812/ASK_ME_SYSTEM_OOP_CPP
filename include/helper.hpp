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

  std::vector<std::string> readFileLines(const std::string&) const;
  void writeFileLines(const std::vector<std::string>&, const std::string&,
                      bool append = true) const;
  std::vector<std::string> splitStringLine(const std::string&,
                                           const std::string& delimiter = ",") const;
  int toInt(const std::string&) const;
  int readInt(const int& min, const int& max) const;
  int showReadMenu(const std::vector<std::string>&) const;
};

#endif