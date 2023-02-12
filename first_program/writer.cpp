#include "writer.h"
#include <string>
#include <numeric>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

using namespace std;

static const char* socket_path = "/tmp/internsocket";
static const unsigned int s_send_len = 50;

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
    char send_msg[s_send_len];
    memset(send_msg, '\0', s_send_len*sizeof(char));
    sprintf(send_msg, "%d", sum);
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        cout << "socket() call error" << endl;
    }
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, socket_path);
    data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    cout << "trying to connect to second_program" << endl;
    if(connect(sock,(struct sockaddr*)& remote, data_len) == -1) {
        cout << "connection call failed" << endl;
        close(sock);
    }
    else {
        cout << "first_program connected" << endl;
    }
    if(send(sock, send_msg, strlen(send_msg)*sizeof(char), 0) == -1) {
        cout << "first_program send() call error" << endl;
    }
    memset(send_msg,'\0', s_send_len*sizeof(char));
    close(sock);
}