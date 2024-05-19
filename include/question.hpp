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

  mutable std::string cachedString;
  mutable bool cachedStringNeedsUpdate = true;

 public:
  Question();
  Question(const std::string&);

  void printQuestionFromUser() const;
  void printQuestionToUser() const;
  void printFeedQuestion() const;
  const std::string& toString() const;

  // Getters
  const int& getQuestionId() const;
  const int& getFromUserId() const;
  const int& getToUserId() const;
  const int& getParentQuestionId() const;
  const int& getIsAnonymousQuestion() const;
  const std::string& getQuestionText() const;
  const std::string& getAnswerText() const;

  // Setters
  void setQuestionId(const int&);
  void setFromUserId(const int&);
  void setToUserId(const int&);
  void setParentQuestionId(const int&);
  void setIsAnonymousQuestion(const int&);
  void setQuestionText(const std::string&);
  void setAnswerText(const std::string&);
};

#endif