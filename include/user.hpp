#ifndef USER_H
#define USER_H 1

#include <cstring>
#include <vector>

class User {
 private:
  int userId;
  std::string name;
  std::string email;
  std::string username;
  std::string password;
  bool allowAnonymousQuestion;
  std::vector<int> questionIdsFrom;
  std::vector<int> questionIdsTo;

 public:
  User();
  User(std::string);
  void readUser();
  void printUser();
  void readUser();
};

#endif