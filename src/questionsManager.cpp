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
          questionsIdsToUser.push_back(std::make_pair(question.getQuestionId(), question.getQuestionId()));
        } else {
          questionsIdsToUser.push_back(std::make_pair(question.getParentQuestionId(), question.getQuestionId()));
        }
      }
    }
  }

  return questionsIdsToUser;
}

void QuestionsManager::printQuestionsToUser(const User& user) const {
  std::cout << "\n";

  const std::map<int, std::vector<int>>& questionIdsToUser = user.getQuestionsIdsToUser();

  if (questionIdsToUser.size() == 0) {
    std::cout << "No Questions\n";
  }

  for (const std::pair<int, std::vector<int>>& pair : questionIdsToUser) {
    for (const int& questionId : pair.second) {
      const Question& question = this->questionsMap.find(questionId)->second;

      question.printQuestionToUser();
    }
  }

  std::cout << "\n";
}

void QuestionsManager::printQuestionsFromUser(const User& user) const {
  std::cout << "\n";

  const std::vector<int>& questionIdsFromUser = user.getQuestionsIdsFromUser();

  if (questionIdsFromUser.size() == 0) {
    std::cout << "No Questions\n";
  }

  for (const int& questionId : questionIdsFromUser) {
    const Question& question = this->questionsMap.find(questionId)->second;

    question.printQuestionFromUser();
  }

  std::cout << "\n";
}

// Used in Answering a question for YOU.
// It can be any of your questions (thread or not)
int QuestionsManager::readAnyQuestionId(const User& user) const {
  int questionId;

  std::cout << "Enter Question id or -1 to cancel: ";
  std::cin >> questionId;

  if (questionId == -1) {
    return -1;
  }

  while (!this->questionsMap.count(questionId)) {
    std::cout << "\nERROR: No question with such id, try again\n\n";
    std::cout << "Enter Question id or -1 to cancel: ";
    std::cin >> questionId;

    if (this->questionsMap.count(questionId)) {
      const Question& question = this->questionsMap.find(questionId)->second;

      if (question.getToUserId() != user.getUserId()) {
        continue;
      } else {
        break;
      }
    }
  }

  return questionId;
}

int QuestionsManager::readyThreadQuestionId(const User& user) const {
  int questionId;

  std::cout << "For thread question: Enter questions id or -1 to cancel: ";
  std::cin >> questionId;

  if (questionId == -1) {
    return -1;
  }

  while (!this->questionsThreadsMap.count(questionId)) {
    std::cout << "\nERROR: No thread question with such id, try again\n\n";
    std::cout << "For thread question: Enter questions id or -1 to cancel: ";
    std::cin >> questionId;
  }

  return questionId;
}

void QuestionsManager::answerQuestion(const User& user) {
  int questionId = this->readAnyQuestionId(user);

  if (questionId == -1) {
    return;
  }

  Question& question = this->questionsMap.find(questionId)->second;

  question.printQuestionToUser();

  if (question.getAnswerText() != "") {
    std::cout << "\nWARNING: Already answered, answer will be updated\n";
  }

  std::cout << "Enter answer: ";

  std::string line;
  std::getline(std::cin, line);
  std::getline(std::cin, line);

  question.setAnswerText(line);
}

void QuestionsManager::deleteQuestion(const User& user) {
  int questionId = this->readAnyQuestionId(user);

  if (questionId == -1) {
    return;
  }

  std::vector<int> questionIdsToRemove;

  if (this->questionsThreadsMap.count(questionId)) {
    questionIdsToRemove = this->questionsThreadsMap[questionId];
    this->questionsThreadsMap.erase(questionId);
  } else {
    questionIdsToRemove.push_back(questionId);

    for (std::pair<const int, std::vector<int>>& pair : this->questionsThreadsMap) {
      std::vector<int>& ids = pair.second;

      for (int i = 0; i < ids.size(); i++) {
        if (questionId == ids[i]) {
          ids.erase(ids.begin() + i);
          break;
        }
      }
    }
  }

  for (const int& id : questionIdsToRemove) {
    this->questionsMap.erase(id);
  }
}

void QuestionsManager::askQuestion(const User& user, const std::pair<int, int>& toUserPair) {
  Question question;

  if (!toUserPair.second) {
    std::cout << "Note: Anonymous questions not allowed for this user\n";

    question.setIsAnonymousQuestion(0);
  } else {
    int status;

    std::cout << "Allow anonymous question or not (1 - 0): ";
    std::cin >> status;

    question.setIsAnonymousQuestion(status);
  }

  question.setParentQuestionId(this->readyThreadQuestionId(user));

  std::string questionText;

  std::cout << "Enter question text: ";
  std::getline(std::cin, questionText);
  std::getline(std::cin, questionText);

  question.setQuestionText(questionText);
  question.setToUserId(toUserPair.first);
  question.setFromUserId(user.getUserId());
  question.setQuestionId(++this->lastId);

  const int& questionId = question.getQuestionId();
  const int& parentQuestionId = question.getParentQuestionId();

  this->questionsMap[questionId] = question;

  if (parentQuestionId == -1) {
    this->questionsThreadsMap[questionId].push_back(questionId);
  } else {
    this->questionsThreadsMap[parentQuestionId].push_back(questionId);
  }
}

void QuestionsManager::listFeed() const {
  for (const std::pair<int, Question>& pair : this->questionsMap) {
    const Question& question = pair.second;

    if (question.getQuestionText() == "") {
      continue;
    }

    question.printFeedQuestion();
  }
}

void QuestionsManager::updateDatabase() const {
  std::vector<std::string> lines;

  for (const std::pair<int, Question>& pair : this->questionsMap) {
    lines.push_back(pair.second.toString());
  }

  Helper::writeFileLines(lines, "database/questions.txt", false);
}