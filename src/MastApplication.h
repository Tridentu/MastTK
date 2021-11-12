#pragma once

#include <CLI11.hpp>
#include <string>
#include <map>

namespace MastTDE {

  enum class MastBackend {
    NCurses = 0,
    TermOx = 1,
  };

  
  class MastApplication {

  public:
    virtual ~MastApplication(){};
    virtual void Run(int arcg, char** argv) = 0;
    virtual const  MastBackend GetBackend() = 0;
    virtual void Init() = 0;
    virtual void AddSubCommand(std::string name, std::string desc) = 0;
    virtual CLI::App* GetSubCommand(std::string name) = 0;

    virtual std::string GetName() = 0;
    virtual std::string GetDescription() = 0;
  };



  
}
