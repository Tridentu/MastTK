#pragma once

#include <termox/widget/widgets/button_list.hpp>
#include <string>
#include "MastString.h"
namespace MastTDE {
  class ButtonMenuTX : public ox::VButton_list {
  public:
    ButtonMenuTX() {}
    virtual MastStringVector GetInitialChoices() = 0;
    virtual void OnMenuChoice(int choice) = 0;
    virtual void AddMenuChoice(MastString title) = 0;
    virtual void SaveChoice(int choice) = 0;
    virtual int GetSelectionCount() = 0;
    virtual void RemoveMenuChoice(std::size_t index) = 0;
    virtual void Init() = 0;
  };
}
