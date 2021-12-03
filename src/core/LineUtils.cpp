#include "LineUtils.hpp"
#include <stdlib.h>
#include <readline/readline.h>

namespace MastTDE {
  const bool LineIO::Confirm(std::string msg) {
    std::stringstream prompt;
    prompt << msg << " (Y/N):" << std::endl;
    bool isInvalid = true;
    bool result = false;
    char* ans = (char*)NULL;
    while(isInvalid){
      ans = readline(prompt.str().c_str());
      std::string response(ans);
      if(response == "Y"){
	isInvalid = false;
	result = true;
      } else if(response == "N"){
	isInvalid = false;
	result = false;
      } else {
	isInvalid = true;
	std::cout << "You must supply a value of Y,y,N or n." << std::endl;
      }
    }
    return result;
  }

  std::string LineIO::Prompt(std::string msg){
    return std::string(readline(msg.c_str()));
  }

  int LineIO::GetChoice(std::vector<std::string> choices){
    std::cout << "Choose one of the following: " << std::endl;
    for (int i = 0; i < choices.size(); ++i){
      std::cout << "   " << (i + 1) << ") " << choices.at(i) << std::endl;
    }
    std::string ans(readline(""));
    int ans_i = -1;
    try {
      ans_i = std::stoi(ans);
    } catch(std::invalid_argument& e){
      std::cerr << "You didn't specify a valid choice." << std::endl;
      return -1;
    }
    if (ans_i - 1 < 0 || ans_i - 1 > choices.size() - 1){
      std::cerr << "You didn't specify a valid choice.";
      return -1;
    }
    return ans_i;
  }

  int LineIO::GetChoice(std::string chooseMsg, std::vector<std::string> choices){
    std::cout << chooseMsg << std::endl;
    std::cout << "Choose one of the following: " << std::endl;
    for (int i = 0; i < choices.size(); ++i){
      std::cout << "   " << (i + 1) << ") " << choices.at(i) << std::endl;
    }
    std::string ans(readline(""));
    int ans_i = -1;
    try {
      ans_i = std::stoi(ans);
    } catch(std::invalid_argument& e){
      std::cerr << "You didn't specify a valid choice." << std::endl;
      return -1;
    }
    if (ans_i - 1 < 0 || ans_i - 1 > choices.size() - 1){
      std::cerr << "You didn't specify a valid choice." << std::endl;
      return -1;
    }
    return ans_i;
  }

  std::vector<std::string> LineIO::GetInputArray(std::string msg, int count){
    std::cout << msg << std::endl;
    std::vector<std::string> entries;
    for (int i = 0; i < count; ++i){
      entries.push_back(std::string(readline("Enter an entry:")));
    }
    return entries;
  }

  std::vector<std::string> LineIO::GetInputArray(std::vector<std::string> msgs, int count){
    std::vector<std::string> entries;
    for (int i = 0; i < count; ++i){
      entries.push_back(std::string(readline(msgs.at(i).c_str())));
    }
    return entries;
  }
  
}
