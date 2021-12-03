#include <CLI11.hpp>
#include "MastNCApplication.h"


namespace MastTDE {
  MastNCApplication::MastNCApplication(const std::string& name){
    m_Name = name;
    m_AppCmd.name(name);
    m_AppCmd.require_subcommand(0);
  }
  

  int MastNCApplication::Run(int argc, const char** argv){
    m_AppCmd.parse(argc, argv);
    return 0;
  }


  void MastNCApplication::AddSubCommand(std::string name, std::string desc){
    m_Subcommands[name] = m_AppCmd.add_subcommand(name, desc);
  }



 CLI::App* MastNCApplication::GetSubCommand(std::string name) {
   return  m_Subcommands[name];
  }
}
