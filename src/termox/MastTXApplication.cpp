


#include <CLI11.hpp>
#include "MastTXApplication.h"
#include <termox/widget/widget.hpp>



namespace MastTDE {
   MastTXApplication::MastTXApplication(const std::string& name){
    m_Name = name;
    m_AppCmd.name(name);
    Init();
 }

  int MastTXApplication::Run(int argc, const char** argv){
    return RunWidget();
  }

   void MastTXApplication::AddSubCommand(std::string name, std::string desc){
    m_Subcommands[name] = m_AppCmd.add_subcommand(name, desc);
  }

 CLI::App* MastTXApplication::GetSubCommand(std::string name) {
   return  m_Subcommands[name];
  }

  

}
