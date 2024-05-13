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