


#pragma once

#include <sys/epoll.h>
#include <vector>

namespace MastTDE {
  struct  IPCClient {
    int fileDescriptor;
    int subscriptions;
    std::string buffer;
    epoll_event event;
    IPCClient(int fileD);    
  };

  typedef std::vector<IPCClient*> IPCClientVector;

  class IPCClientManager{
  public:
    IPCClientManager(){};
    ~IPCClientManager(){};
  protected:
    IPCClientVector clients;
  public:
    void AddClient(IPCClient* client);
    void RemoveClient(IPCClient* client);
    IPCClient* GetClient(int fileDescriptor);
  };
}
