#pragma once

#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace MastTDE {
  class LineIO {
  public:
    static const bool Confirm(std::string msg);
    static std::string Prompt(std::string msg);
    static int GetChoice(std::vector<std::string> choices);
    static int GetChoice(std::string chooseMsg, std::vector<std::string> choices);
    static std::vector<std::string> GetInputArray(std::string msg, int count);
    static std::vector<std::string> GetInputArray(std::vector<std::string> msgs, int count);
  };
}
