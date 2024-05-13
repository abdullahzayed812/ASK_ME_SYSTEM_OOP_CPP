#ifndef USER_H
#define USER_H 1

#include <util.h>

#include <cstring>
#include <map>
#include <vector>

class User {
 private:
  int userId;
  std::string name;
  std::string email;
  std::string username;
  std::string password;
  int allowAnonymousQuestions;

  std::vector<int> questionIdsFromUser;
  std::map<int, std::vector<int>> questionIdsToUser;

  const int& getUserId() const;
  const std::string& getName() const;
  const std::string& getEmail() const;
  const std::string& getUsername() const;
  const std::string& getPassword() const;
  const int& getAllowAnonymousQuestions() const;
  const std::vector<int>& getQuestionsFromUser() const;
  const std::map<int, std::vector<int>>& getQuestionsToUser() const;

  void setUserId(const int&);
  void setName(const std::string&);
  void setEmail(const std::string&);
  void setUsername(const std::string&);
  void setPassword(const std::string&);
  void setAllowAnonymousQuestions(const int&);

 public:
  User();
  User(const std::string&);
  const std::string& toString() const;
  void print() const;
  void resetQuestionsFromUser(const std::vector<int>&);
  void resetQuestionsToUser(const std::vector<std::pair<int, int>>&);
  void readUser(const std::string&, const int& id);
};

#endif