
#include <string>
#include <cstring>
#include <iostream>
#include <sys/epoll.h>
#include "IPCClient.hpp"
namespace MastTDE {
  IPCClient::IPCClient(int fd){
    std::memset(&event, 0, sizeof(epoll_event));
    fileDescriptor = fd;
    event.data.fd = fileDescriptor;
    subscriptions = 0;
  }

  void IPCClientManager::AddClient(IPCClient* client){
    std::cout << "Adding client with fd " << client->fileDescriptor << " to list..." << std::endl;
    clients.push_back(client);
  }

  void IPCClientManager::RemoveClient(IPCClient* client){
    int it;
    for (size_t i = 0; i < clients.size(); ++i){
      if(clients.at(i)->fileDescriptor == client->fileDescriptor){
	it = i;
	break;
      }
    }
    if (clients.begin() + it != clients.end())
      clients.erase(clients.begin() + it);
  }

  IPCClient* IPCClientManager::GetClient(int fd){
    IPCClient* cli;
    for (size_t i = 0; i < clients.size(); ++i){
      if(clients.at(i)->fileDescriptor == fd){
	cli = clients.at(i);
	break;
      }
    }
    if (cli)
      return cli;
    return NULL;
  }
  
}
