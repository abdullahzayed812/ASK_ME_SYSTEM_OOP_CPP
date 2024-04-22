#ifndef USERS_MANAGER
#define USERS_MANAGER 1

#include "user.hpp"

class UsersManager {
 private:
  User currentUser;
  int lastId;

 public:
  void login();
  void signUp();
  void loadUsers();
};

#endif