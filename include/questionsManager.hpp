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
};

#endif