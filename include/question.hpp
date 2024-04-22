#ifndef QUESTION_H
#define QUESTION_H 1

#include <cstring>

class Question {
 private:
  int questionId;
  int fromUserId;
  int toUserId;
  int parentQuestionId;

 public:
  Question();
  Question(std::string);
  void printFromQuestion();
  void printToQuestion();
  void printFeedQuestion();
  void readQuestion();
};

#endif