#ifndef ASK_SYSTEM_H
#define ASK_SYSTEM_H 1

#include "questionsManager.hpp"
#include "usersManager.hpp"

class AskSystem {
 private:
  UsersManager usersManager;
  QuestionsManager questionsManager;

 public:
  void loadDatabase(bool fillUserQuestions = false);
  void resetCurrentUserQuestions();
  void run();
};

#endif