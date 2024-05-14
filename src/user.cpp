#include "../include/user.hpp"

#include <assert.h>

#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "../include/helper.hpp"

User::User() : userId(-1), allowAnonymousQuestions(-1) {}

User::User(const std::string& line) {
  std::vector<std::string> userData = Helper::splitStringLine(line);

  assert(userData.size() == 6);

  this->userId = Helper::toInt(userData[0]);
  this->name = userData[1];
  this->password = userData[2];
  this->username = userData[3];
  this->email = userData[4];
  this->allowAnonymousQuestions = Helper::toInt(userData[5]);
}

const std::string& User::toString() const {
  std::ostringstream oss;

  oss << this->userId << "," << this->name << "," << this->password << "," << this->username << ","
      << this->email << "," << this->allowAnonymousQuestions;

  return oss.str();
}

void User::print() const {
  std::cout << "User: " << this->userId << ", " << this->username << ", " << this->password << ", "
            << this->name << ", " << ", " << this->email << "\n";
}

void User::resetQuestionsFromUser(const std::vector<int>& newQuestions) {
  this->questionIdsFromUser.clear();

  std::vector<int>::const_iterator it;

  for (it = newQuestions.begin(); it != newQuestions.end(); it++) {
    this->questionIdsFromUser.push_back(*it);
  }
}

void User::resetQuestionsToUser(const std::vector<std::pair<int, int>>& newQuestionsPair) {
  this->questionIdsToUser.clear();

  std::vector<std::pair<int, int>>::const_iterator it;

  for (it = newQuestionsPair.begin(); it != newQuestionsPair.end(); it++) {
    this->questionIdsToUser[(*it).first].push_back((*it).second);
  }
}

const int& User::getUserId() const { return this->userId; }

const std::string& User::getName() const { return this->name; }

const std::string& User::getEmail() const { return this->email; }

const std::string& User::getUsername() const { return this->username; }

const std::string& User::getPassword() const { return this->password; }

const int& User::getAllowAnonymousQuestions() const { return this->allowAnonymousQuestions; }

const std::vector<int>& User::getQuestionsIdsFromUser() const { return this->questionIdsFromUser; }

const std::map<int, std::vector<int>>& User::getQuestionsIdsToUser() const {
  return this->questionIdsToUser;
}

void User::setUserId(const int& userId) { this->userId = userId; }

void User::setName(const std::string& name) { this->name = name; }

void User::setEmail(const std::string& email) { this->email = email; }

void User::setUsername(const std::string& username) { this->username = username; }

void User::setPassword(const std::string& password) { this->password = password; }

void User::setAllowAnonymousQuestions(const int& allowAnonymousQuestion) {
  this->allowAnonymousQuestions = allowAnonymousQuestion;
}
