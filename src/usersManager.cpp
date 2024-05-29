#include "../include/usersManager.hpp"

#include <iostream>
#include <map>
#include <vector>

#include "../include/helper.hpp"
#include "../include/user.hpp"

UsersManager::UsersManager() { this->lastId = 0; }

void UsersManager::loadDatabase() {
  this->lastId = 0;
  this->usersMap.clear();

  std::vector<std::string> lines = Helper::readFileLines("database/users.txt");

  for (const std::string line : lines) {
    User user(line);

    this->usersMap[user.getUsername()] = user;
    this->lastId = std::max(this->lastId, user.getUserId());
  }
}

void UsersManager::accessSystem() {
  const int& choice = Helper::showReadMenu({"Login", "Sign Up"});

  if (choice == 1) {
    this->login();
  } else {
    this->signUp();
  }
}

void UsersManager::login() {
  this->loadDatabase();  // in case user added from other parallel run

  while (true) {
    std::string username;
    std::string password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::cin >> password;

    this->currentUser.setUsername(username);
    this->currentUser.setPassword(password);

    if (!this->usersMap.count(username)) {
      std::cout << "\nInvalid username or password, try again.\n\n";
      continue;
    }

    const User& userExists = this->usersMap[username];

    if (userExists.getPassword() != password) {
      std::cout << "\nInvalid username or password, try again.\n\n";
      continue;
    }

    this->currentUser = userExists;
    break;
  }
}

void UsersManager::signUp() {
  std::string username;

  while (true) {
    std::cout << "Enter username: ";
    std::getline(std::cin, username);

    if (this->currentUser.getUsername() == username) {
      std::cout << "\nAlready exists.\n\n";
    } else {
      break;
    }
  }

  this->currentUser.readUser(username, ++lastId);
  this->usersMap[username] = this->currentUser;

  this->updateDatabase(this->currentUser);
}

void UsersManager::updateDatabase(const User& newUser) {
  std::string line = newUser.toString();
  std::vector<std::string> lines(1, line);

  Helper::writeFileLines("database/users.txt", lines);
}

void UsersManager::resetQuestionsToUser(const std::vector<std::pair<int, int>>& questionsToUser) {
  this->currentUser.resetQuestionsToUser(questionsToUser);
}

void UsersManager::resetQuestionsFromUser(const std::vector<int>& questionsFromUser) {
  this->currentUser.resetQuestionsFromUser(questionsFromUser);
}

void UsersManager::listUsersNamesIds() const {
  for (const std::pair<std::string, User>& pair : this->usersMap) {
    std::cout << "ID: " << pair.second.getUserId() << "\t\tName: " << pair.second.getUsername() << "\n";
  }
}

const User& UsersManager::getCurrentUser() const { return this->currentUser; }

std::pair<int, int> UsersManager::readUserId() const {
  int userId;

  std::cout << "Enter user id or -1 to cancel: ";
  std::cin >> userId;

  if (userId == -1) {
    std::make_pair(-1, -1);
  }

  for (const std::pair<std::string, User>& pair : this->usersMap) {
    if (pair.second.getUserId() == userId) {
      return std::make_pair(userId, pair.second.getAllowAnonymousQuestions());
    }
  }

  std::cout << "Invalid user id, try again.\n";
  this->getCurrentUser();
}
