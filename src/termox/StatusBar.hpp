#pragma once

#include <termox/widget/widgets/banner.hpp>

#include "MastString.h"


namespace MastTDE {
  class StatusBar {
  public:
    virtual MastString GetText() = 0;
    virtual MastString SetText() = 0;
    virtual std::unique_ptr<ox::Scan_banner> GetScanBanner() = 0;
  }
}
