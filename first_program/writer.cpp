#include "writer.h"
#include <string>
#include <numeric>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

static const char* socket_path = "/tmp";
static const unsigned int s_recv_len = 100;
static const unsigned int s_send_len = 50;

using namespace std;
void Writer::process_data() {
    while(true) {
        auto lock = _buffer.lock();
        _buffer.sleep_until_notified(lock);
        string processing_data = _buffer.get_data();
        _buffer.clear_data();
        lock.unlock();
        int sum = calc_sum(processing_data);
        print(processing_data, sum);
        transfer(sum);
    }
    //to be continued
}
int Writer::calc_sum(string& processing_data) {
    int sum = 0;
    for (char ch :processing_data) {
        if(isdigit(ch)) {
            sum += ch - '0';
        }
    }
    return sum;
}
void Writer::print(std::string& processing_data, int sum) {
    cout << "the string is: " << processing_data << endl;
    cout << "sum of digits: " << sum << endl;
}
void Writer::transfer(int& sum) {
    int sock = 0;
    int data_len = 0;
    struct sockaddr_un remote;
    char recv_msg[s_recv_len];
    char send_msg[s_send_len];
    
    memset(recv_msg,0, s_recv_len*sizeof(char));
    memset(send_msg,0, s_send_len*sizeof(char));

    sprintf(send_msg, "%d", sum);

    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        throw runtime_error("socket call error");
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, socket_path);
    data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    cout << "trying to connect to second_program" << endl;

    if(connect(sock,(struct sockaddr*)& remote, data_len) == -1) {
        throw runtime_error("connection call failed");
    }

    cout << "first_program connected" <<endl;

    if(send(sock, send_msg, strlen(send_msg)*sizeof(char), 0) == -1) {
        throw runtime_error("first_program send() call error");
    }

    memset(recv_msg,0, s_recv_len*sizeof(char));
    memset(send_msg,0, s_send_len*sizeof(char));

    if((data_len = recv(sock, recv_msg, s_recv_len, 0)) > 0) {
        cout << "first_program successfully sent data:" << recv_msg <<endl;
    }
    else {
        if(data_len < 0) {
            throw runtime_error("first program recv() call error");
        }
        else {
        cout << "first_program socket closed" <<endl;
        close(sock);
        }
    }
}