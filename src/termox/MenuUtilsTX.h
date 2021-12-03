#pragma once

#include <termox/widget/widgets/menu.hpp>
#include <string>
#include "../core/MastString.h"
#include <map>


namespace MastTDE {
  class MenuTX  {
  public:
    MenuTX() {}
    virtual MastStringVector GetInitialChoices() = 0;
    virtual void OnMenuChoice(int choice) = 0;
    virtual void AddMenuChoice(MastString title) = 0;
    virtual void SaveChoice(int choice) = 0;
    virtual int GetSelectionCount() = 0;
    virtual void RemoveMenuChoice(std::size_t index) = 0;
    virtual void Init() = 0;
    virtual std::unique_ptr<ox::Menu> GetMenu() = 0;
    
  };

}
