#ifndef QUESTION_H
#define QUESTION_H 1

#include <string>

class Question {
 private:
  int questionId;
  int fromUserId;
  int toUserId;
  int parentQuestionId;
  bool isAnonymousQuestions;

  std::string questionText;
  std::string answerText;

 public:
  Question();
  Question(std::string);

  void printFromQuestion();
  void printToQuestion();
  void printFeedQuestion();
  void readQuestion();
};

#endif