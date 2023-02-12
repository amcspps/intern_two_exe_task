#pragma once
#include "buffer.h"
#include <string>

class Writer {
public:
    Writer(Buffer& buffer):_buffer(buffer) {};
    void process_data();
    int calc_sum(std::string& processing_data);
    void print(std::string& processing_data, int sum);
    void transfer(int& sum);
private:
    Buffer& _buffer;
};