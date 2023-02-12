#pragma once 
#include <cstring>

static const unsigned int s_recv_len = 50;

class Receiver {
public:
    Receiver() { memset(_recv_buf, '\0',s_recv_len*sizeof(char));};
    void receive();
    void analyze();
    void print(int&& value);
private:
    char _recv_buf[s_recv_len];
};