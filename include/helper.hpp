#ifndef HELPER_H
#define HELPER_H 1

#include <string>
#include <vector>

class Helper {
 public:
  Helper();
  
  static std::vector<std::string> readFileLines(const std::string&);
  static void writeFileLines(const std::vector<std::string>&, const std::string&,
                             bool append = true);
  static std::vector<std::string> splitStringLine(const std::string&,
                                                  const std::string& delimiter = ",");
  static int toInt(const std::string&);
  static int readInt(const int& min, const int& max);
  static int showReadMenu(const std::vector<std::string>&);
};

#endif