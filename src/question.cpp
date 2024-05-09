#include "../include/question.hpp"

#include <iostream>
#include <sstream>

#include "../include/helper.hpp"

Question::Question()
    : questionId(-1), parentQuestionId(-1), fromUserId(-1), toUserId(-1), isAnonymousQuestion(1) {}

Question::Question(const std::string& line) {
  std::vector<std::string> questionData = Helper::splitStringLine(line);

  this->questionId = Helper::toInt(questionData[0]);
  this->parentQuestionId = Helper::toInt(questionData[1]);
  this->fromUserId = Helper::toInt(questionData[2]);
  this->toUserId = Helper::toInt(questionData[3]);
  this->isAnonymousQuestion = Helper::toInt(questionData[4]);
  this->questionText = questionData[5];
  this->answerText = questionData[6];
}

void Question::printQuestionFromUser() const {
  std::cout << "Question id ( " << this->questionId << " )";

  if (!this->isAnonymousQuestion) {
    std::cout << " !AQ,";
  }

  std::cout << " to user id ( " << this->toUserId << " )\n";
  std::cout << "\t question: " << this->questionText << "\n";

  if (this->answerText != "") {
    std::cout << "\t answer: " << this->answerText << "\n";
  } else {
    std::cout << "\tNOT answered yet\n";
  }
}

void Question::printQuestionToUser() const {
  std::string prefix = "";

  if (this->parentQuestionId != -1) {
    prefix = "Thread";
  }

  std::cout << "Question id ( " << this->questionId << " )";

  if (!this->isAnonymousQuestion) {
    std::cout << " from user id ( " << this->fromUserId << " )";
  }

  std::cout << "\n\t question: " << this->questionText << "\n";

  if (this->answerText != "") {
    std::cout << "\t answer: " << this->answerText << "\n";
  }

  std::cout << "\n";
}

void Question::printFeedQuestion() const {
  if (this->parentQuestionId != -1) {
    std::cout << "Thread parent question id ( " << this->parentQuestionId << " )";
  }

  std::cout << "\t question id ( " << this->questionId << " )";

  if (!this->isAnonymousQuestion) {
    std::cout << " from user id ( " << this->fromUserId << " )";
  } else {
    std::cout << " ,AQ ";
  }

  std::cout << " to user id ( " << this->toUserId << " )";
  std::cout << "\n\t question: " << this->questionText << "\n";

  if (this->answerText != "") {
    std::cout << "\t answer: " << this->answerText << "\n";
  }
}

const std::string& Question::toString() const {
  std::ostringstream oss;

  oss << this->questionId << ", " << this->parentQuestionId << ", " << this->fromUserId << ", "
      << this->toUserId << ", " << this->isAnonymousQuestion << ", " << this->questionText << ", "
      << this->answerText;

  return oss.str();
}