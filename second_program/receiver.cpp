#include "receiver.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

using namespace std;

static const char* socket_path = "/tmp/internsocket";
static const unsigned int incoming_connections_num = 5;

void Receiver::receive() {
    int s = 0;
    int s2 = 0;
    struct sockaddr_un local, remote;
    int len = 0;
    s = socket(AF_UNIX, SOCK_STREAM, 0);
    if( s == -1) {
        cout << "socket() call error"; 
    }
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, socket_path);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s,(struct sockaddr*)&local, len) != 0) {
        cout << "error on binding socket" << endl;
    }
    if(listen(s, incoming_connections_num) !=0) {
        cout << "error on listen call" << endl;
    }
    
    while(true) {
        unsigned int sock_len = 0;
        cout << "waiting for connection..." << endl;
        if ((s2 = accept(s, (struct sockaddr*)&remote, &sock_len)) == -1) {
            cout << "error on accept() call" << endl;
        }
        cout << "connection established" << endl;
        int data_recv = 0;
        do {
            memset(_recv_buf, '\0',s_recv_len*sizeof(char));
            data_recv = recv(s2, _recv_buf, s_recv_len, 0);
            if(data_recv > 0) {
                analyze();
            }
        } while(data_recv > 0);
        close(s2);
    }
    
}

void Receiver::analyze() {
    if(strlen(_recv_buf) > 2 && (atoi(_recv_buf)%32 == 0)) {
        print(atoi(_recv_buf));
    }
    else {
        cout << "received sum is wrong" << endl;
    }
}

void Receiver::print(int&& value) {
    cout << "received sum is: "<< value << endl;
}