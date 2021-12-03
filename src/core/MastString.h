#pragma once
#include <termox/painter/glyph_string.hpp>
#include <termox/painter/glyph.hpp>
#include <termox/painter/trait.hpp>
#include <string>
#include <iostream>
#include <string_view>

namespace MastTDE {

  class MastString {

  public:
    MastString() = default;
    MastString(const std::string& text);
    MastString(const char* text);
    MastString(const MastString& other) = default;
    ~MastString(){}
  public:
    const char* c_str(){ return m_String.c_str();  }
    std::string& string() { return m_String; }
    ox::Glyph_string g_str() {
      ox::Glyph_string str = ox::Glyph_string(std::string_view(m_String));
      return str;
    }
    friend std::ostream& operator<<(std::ostream& os, const MastString& str);
    
    std::istream& operator>> (std::istream is){
      is >> string();
      return is;
    };
  public:
    ox::Glyph_string Traitify(ox::Traits ts){
      return g_str() | ts;
    }
    ox::Glyph_string ColorizeBG(ox::Background_color bg){
      return g_str() | bg;
    }
    ox::Glyph_string ColorizeFG(ox::Foreground_color fg){
      return g_str() | fg;
    }
    ox::Glyph_string Brushify(ox::Brush brush){
      return g_str() | brush;
    }
    bool operator==(MastString& y){
      return g_str() == y.g_str() || string() == y.string();
    }
    bool operator!=(MastString& y){
      return g_str() != y.g_str();
    }

   MastString operator+(MastString& x){
    return MastString(this->string() + x.string());
  }
    bool empty() {
      return m_String.empty();
    }
  private:
    std::string m_String;
  };

  
 

 


  typedef std::vector<MastString> MastStringVector;
  
}
