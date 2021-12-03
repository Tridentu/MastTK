
#pragma once


#include <string>


namespace MastTDE {
    union ArgumentPacket {
      long i;
      unsigned long ui;
      float f;
      std::string  str;
      const void* anyObj;
    };
}
