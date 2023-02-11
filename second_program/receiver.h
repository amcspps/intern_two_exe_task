#pragma once 
static const unsigned int s_recv_len = 50;
class Receiver {
public:
    Receiver();
    void receive();
    void analyze();
    void print(int&& value);
private:
    char _recv_buf[s_recv_len];
};