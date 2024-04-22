#ifndef QUESTIONS_MANAGER
#define QUESTIONS_MANAGER 1

#include <map>

#include "question.hpp"

class QuestionsManager {
 private:
  std::map<int, std::vector<int>> questionsThreads;
  std::vector<Question> questions;
  int lastId;

 public:
  void loadDatabase();
};

#endif