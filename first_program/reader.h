#pragma once
#include <iostream>
#include <string>
#include "buffer.h"
class Reader {
public:
  Reader(Buffer& buffer):_buffer(buffer) {};
  std::string read_data();
  bool check(std::string& str);
  std::string sort_replace(std::string& str);

  void run();

  private:
  Buffer& _buffer;
};