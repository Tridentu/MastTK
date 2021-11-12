#pragma once
#include <termox/termox.hpp>
#include <CLI11.hpp>
#include <string>
#include "MastApplication.h"
#include <map>


namespace MastTDE {
  
  class MastTXApplication : public MastApplication {
  public:
    MastTXApplication(const std::string& name, std::string desc);
    ~MastTXApplication(){ delete m_AppCmd; }
    virtual void Run(int argc, char** argv) override;
    virtual const MastBackend GetBackend() override { return MastBackend::TermOx; }
    virtual void Init() override {};
    virtual void AddSubCommand(std::string name, std::string desc) override;
    virtual CLI::App* GetSubCommand(std::string name) override;
    virtual std::string GetName() override { return m_Name; }
    virtual std::string GetDescription() override { return m_Desc; }
  private:
    std::map<std::string, ox::Widget> m_Menus;
    std::string m_Name;
    std::string m_Desc;
    CLI::App* m_AppCmd;
    std::map<std::string, CLI::App*> m_Subcommands;
  };

}
