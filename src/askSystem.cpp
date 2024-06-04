#include "../include/askSystem.hpp"

#include <map>
#include <utility>
#include <vector>

#include "../include/helper.hpp"
#include "../include/questionsManager.hpp"
#include "../include/user.hpp"
#include "../include/usersManager.hpp"

void AskSystem::loadDatabase(bool fillUserQuestions) {
  this->questionsManager.loadDatabase();
  this->usersManager.loadDatabase();

  if (fillUserQuestions) {
    this->resetCurrentUserQuestions();
  }
}

/*
 * Probably the most important design change
 * We needed to decouple the question manager from relying on User implementation
 * We break to 2 steps
 * 1) Question manager return relevant question
 * 2) User manager helps reseting the user question. Even the manager doesn't do this by itself
 *
 * This is more OO now
 */
void AskSystem::resetCurrentUserQuestions() {
  const User& user = usersManager.getCurrentUser();

  const std::vector<std::pair<int, int>>& questionsToUser = this->questionsManager.getQuestionsIdsToUser(user);
  usersManager.resetQuestionsToUser(questionsToUser);

  const std::vector<int>& questionsFromUser = this->questionsManager.getQuestionsIdsFromUser(user);
  usersManager.resetQuestionsFromUser(questionsFromUser);
}

void AskSystem::run() {
  this->loadDatabase();
  this->usersManager.accessSystem();
  this->resetCurrentUserQuestions();

  std::vector<std::string> menu;
  menu.push_back("Print Questions To Me");
  menu.push_back("Print Questions From Me");
  menu.push_back("Answer Question");
  menu.push_back("Delete Question");
  menu.push_back("Ask Question");
  menu.push_back("List System Users");
  menu.push_back("Feed");
  menu.push_back("Logout");

  const User& currentUser = usersManager.getCurrentUser();

  while (true) {
    const int choice = Helper::showReadMenu(menu);

    this->loadDatabase(true);

    if (choice == 1) {
      this->questionsManager.printQuestionsToUser(currentUser);
    } else if (choice == 2) {
      this->questionsManager.printQuestionsFromUser(currentUser);
    } else if (choice == 3) {
      this->questionsManager.answerQuestion(currentUser);
      this->questionsManager.updateDatabase();
    } else if (choice == 4) {
      this->questionsManager.deleteQuestion(currentUser);
      this->resetCurrentUserQuestions();
      this->questionsManager.updateDatabase();
    } else if (choice == 5) {
      std::pair<int, int> userIdAndAllowAnonymousQuestionPair = usersManager.readUserId();

      if (userIdAndAllowAnonymousQuestionPair.first != -1) {
        this->questionsManager.askQuestion(currentUser, userIdAndAllowAnonymousQuestionPair);
        this->questionsManager.updateDatabase();
      }
    } else if (choice == 6) {
      this->usersManager.listUsersNamesIds();
    } else if (choice == 7) {
      this->questionsManager.listFeed();
    } else
      break;
  }

  this->run();
}