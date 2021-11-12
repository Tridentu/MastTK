#include <CLI11.hpp>
#include "MastNCApplication.h"


namespace MastTDE {
  MastNCApplication::MastNCApplication(const std::string& name, std::string desc){
    m_Name = name;
    m_Desc = desc;
    m_AppCmd.name(name);
    m_AppCmd.description(desc);
  }
  

  void MastNCApplication::Run(int argc, char** argv){
    m_AppCmd.parse(argc, argv);
  }


  void MastNCApplication::AddSubCommand(std::string name, std::string desc){
    m_Subcommands[name] = m_AppCmd.add_subcommand(name, desc);
  }



 CLI::App* MastNCApplication::GetSubCommand(std::string name) {
   return  m_Subcommands[name];
  }
}
