#pragma once

#include <CLI11.hpp>
#include "MenuUtils.h"
#include <termox/widget/widget.hpp>
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

  class MastNCApplication : public MastApplication {
  public:
    MastNCApplication(const std::string& name, std::string desc);
    ~MastNCApplication(){ delete m_AppCmd; }
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
    CLI::App* m_AppCmd;
    std::string m_Desc;
    std::map<std::string, CLI::App*> m_Subcommands;

  };

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
