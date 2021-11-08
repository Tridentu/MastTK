
#include <stdlib.h>
#include <string>
#include <functional>

namespace MastTK {
  bool runAsUser(std::string username, std::function<void()> action);
  
}
