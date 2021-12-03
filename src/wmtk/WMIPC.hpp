

#pragma once

#include <string>
#include <functional>
#include "../core/GenericUtils2.hpp"
#include "../core/IPCClient.hpp"

namespace MastTDE {
  enum class IPCMessageType  {
    Command  = 0,
    Monitors = 1,
    Tags = 2,
    Layouts = 3,
    Client = 4,
    Subscribe = 5,
    Event = 6,
  };

  enum class IPCEvent {
    TagChange = 1 << 0,
    ClientFocusChange = 1 << 1,
    LayoutChange = 1 << 2,
    MonitorFocusChange = 1 << 3,
    FocusedTitleChange = 1 << 4,
    FocusedStateChange = 1 << 5
  };

  enum class IPCSubscriptionAction {
    ActionUnsubscribe = 0,
    ActionSubscribe = 1
  };

  enum class ArgType {
    None = 0,
    UInt,
    SInt,
    Float,
    Ptr,
    String
  };

  union ArgFunction {
    std::function<void(const ArgumentPacket*)> singleParam;
    std::function<void(const ArgumentPacket*, int)> arrayParam;
  };

  struct IPCCommand {
    std::string name;
    ArgFunction funct;
    uint32_t argc;
    ArgType *arg_types;
  };

  struct IPCParsedCommand {
    std::string name;
    ArgumentPacket *args;
    ArgType *arg_types;
    uint32_t argc;
  };

  typedef std::vector<IPCCommand> IPCCommandVector;
}

#define IPCCOMMAND(FUNC,ARGC,TYPES)  \
  { #FUNC, {FUNC}. ARGC (ArgType[ARGC])TYPES}


