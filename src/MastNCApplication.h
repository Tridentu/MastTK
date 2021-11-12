#pragma once
#include "MenuUtils.h"
#include <CLI11.hpp>
#include "MastApplication.h"
#include <string>
#include <map>

namespace MastTDE {

    class MastNCApplication : public MastApplication {
  public:
    MastNCApplication(const std::string& name, std::string desc);
    ~MastNCApplication(){  }
    virtual void Run(int argc, char** argv) override;
    virtual const MastBackend GetBackend() override { return MastBackend::NCurses; }
    virtual void Init() override {};
    virtual void AddSubCommand(std::string name, std::string desc) override;
    virtual CLI::App* GetSubCommand(std::string name) override;
    virtual std::string GetName() override { return m_Name; }
    virtual std::string GetDescription() override { return m_Desc; }
  public:
    virtual void RunMenuContainer(std::string name) = 0;
  private:
    std::map<std::string, MenuContainer*> m_Menus;
    std::string m_Name;
    CLI::App m_AppCmd;
    std::string m_Desc;
    std::map<std::string, CLI::App*> m_Subcommands;

  };
}
