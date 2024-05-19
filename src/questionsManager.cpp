#include "../include/questionsManager.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "../include/helper.hpp"
#include "../include/question.hpp"

QuestionsManager::QuestionsManager() { this->lastId = 0; }

void QuestionsManager::loadDatabase() {
  this->lastId = 0;

  this->questionsMap.clear();
  this->questionsThreadsMap.clear();

  std::vector<std::string> lines = Helper::readFileLines("database/questions.txt");
  std::vector<std::string>::const_iterator it;

  for (it = lines.cbegin(); it != lines.cend(); it++) {
    Question question(*it);

    this->lastId = std::max(this->lastId, question.getQuestionId());

    this->questionsMap[question.getQuestionId()] = question;

    if (question.getParentQuestionId() != -1) {
      this->questionsThreadsMap[question.getParentQuestionId()].push_back(question.getQuestionId());
    } else {
      this->questionsThreadsMap[question.getQuestionId()].push_back(question.getQuestionId());
    }
  }
}

std::vector<int> QuestionsManager::getQuestionsIdsFromUser(const User& user) const {
  std::vector<int> questionsIdsFromUser;

  for (const std::pair<int, std::vector<int>>& pair : this->questionsThreadsMap) {
    for (const int& questionId : pair.second) {
      const Question& question = this->questionsMap.find(questionId)->second;

      if (question.getFromUserId() == user.getUserId()) {
        questionsIdsFromUser.push_back(question.getQuestionId());
      }
    }
  }

  return questionsIdsFromUser;
}

std::vector<std::pair<int, int>> QuestionsManager::getQuestionsIdsToUser(const User& user) const {
  std::vector<std::pair<int, int>> questionsIdsToUser;

  for (const std::pair<int, std::vector<int>>& pair : this->questionsThreadsMap) {
    for (const int& questionId : pair.second) {
      const Question& question = this->questionsMap.find(questionId)->second;

      if (question.getToUserId() == user.getUserId()) {
        if (question.getParentQuestionId() == -1) {
          questionsIdsToUser.push_back(
              std::make_pair(question.getQuestionId(), question.getQuestionId()));
        } else {
          questionsIdsToUser.push_back(
              std::make_pair(question.getParentQuestionId(), question.getQuestionId()));
        }
      }
    }
  }

  return questionsIdsToUser;
}