
#include "MastString.h"
#include <string>


namespace MastTDE {
  MastString::MastString(const std::string& text) : m_String(text){}
  MastString::MastString(const char* text) : m_String(std::string(text)) {}
   std::ostream& operator<<(std::ostream& os, const MastString& str){
       os << str.m_String;
      return os;
    };

}
