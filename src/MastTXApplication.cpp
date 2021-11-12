


#include <CLI11.hpp>
#include "MastTXApplication.h"
#include <termox/widget/widget.hpp>



namespace MastTDE {
   MastTXApplication::MastTXApplication(const std::string& name, std::string desc){
    m_Name = name;
    m_Desc = desc;
    m_AppCmd = m_AppCmd->name(name)->description(desc);

 }

  void MastTXApplication::Run(int argc, char** argv){
    m_AppCmd->parse(argc, argv);
  }

   void MastTXApplication::AddSubCommand(std::string name, std::string desc){
    m_Subcommands[name] = m_AppCmd->add_subcommand(name, desc);
  }

 CLI::App* MastTXApplication::GetSubCommand(std::string name) {
   return  m_Subcommands[name];
  }

}
