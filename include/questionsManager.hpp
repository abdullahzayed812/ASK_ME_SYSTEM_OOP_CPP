#ifndef QUESTIONS_MANAGER
#define QUESTIONS_MANAGER 1

#include <map>
#include <vector>

#include "question.hpp"
#include "user.hpp"

class QuestionsManager {
 private:
  std::map<int, std::vector<int>> questionsThreadsMap;
  std::map<int, Question> questionsMap;

  int lastId;

 public:
  QuestionsManager();
  void loadDatabase();
  std::vector<int> getQuestionsIdsFromUser(const User&) const;
  std::vector<std::pair<int, int>> getQuestionsIdsToUser(const User&) const;
  void printQuestionsToUser(const User&) const;
  void printQuestionsFromUser(const User&) const;
  int readAnyQuestionId(const User&) const;
  int readyThreadQuestionId(const User&) const;
  void answerQuestion(const User&);
  void deleteQuestion(const User&);
};

#endif