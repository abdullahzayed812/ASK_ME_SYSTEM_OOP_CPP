
#include <iostream>
#include <vector>

#include "../include/helper.hpp"

int main() {
  Helper* helper = Helper::createHelper();

  helper->showReadMenu({"Learn c++", "Learn Java", "Learn c#", "Learn python"});

  Helper::freeHelper();

  return 0;
}