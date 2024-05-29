#ifndef USERS_MANAGER
#define USERS_MANAGER 1

#include "user.hpp"

class UsersManager {
 private:
  std::map<std::string, User> usersMap;
  User currentUser;
  int lastId;

 public:
  UsersManager();
  void loadDatabase();
  void accessSystem();
  void login();
  void signUp();
  void updateDatabase(const User&);
};

#endif