

#pragma once
#include <iostream>
#include <stdlib.h>
namespace MastTDE {
  void Exit(std::string msg){
    std::cerr << msg << std::endl;
    exit(1);
  };
  void *ECalloc(size_t nMemB,size_t size){
       void *p;
      if (!(p = calloc(nMemB, size)))
	Exit("Calloc:");
      return p;
  }

  
}
