#ifndef QUESTION_H
#define QUESTION_H 1

#include <string>

class Question {
 private:
  int questionId;
  int fromUserId;
  int toUserId;
  int parentQuestionId;
  int isAnonymousQuestion;

  std::string questionText;
  std::string answerText;

 public:
  Question();
  Question(const std::string&);

  void printQuestionFromUser() const;
  void printQuestionToUser() const;
  void printFeedQuestion() const;
  const std::string& toString() const;
};

#endif