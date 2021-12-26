// Macro expansion playground.
// g++ -std=c++11 -E -DPLAYGROUND_ONLY src/variad/cpp/playground2.cpp

#ifndef PLAYGROUND_ONLY
#include <memory>
#include <string>
#include <iostream>
#endif

#include "for_each.hpp"

int main(int argc, char **argv) { 
  std::cout << "hello, world!" << std::endl;
  return 0; 
}
