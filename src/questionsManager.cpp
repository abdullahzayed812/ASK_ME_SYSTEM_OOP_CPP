#include "../include/questionsManager.hpp"

#include <iostream>
#include <map>
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