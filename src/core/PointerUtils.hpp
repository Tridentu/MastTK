#pragma once
#include <string>


namespace MastTDE {
  template<typename T, typename F>
  std::unique_ptr<T> unique_cast(std::unique_ptr<F> from){
    return std::unique_ptr<T>(std::static_cast<T>(from.release()));
  };
}
