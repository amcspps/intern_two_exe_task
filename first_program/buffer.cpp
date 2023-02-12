#include "buffer.h"

using namespace std;

string Buffer::get_data() {
    return _data;
}

void Buffer::set_data(string data) {
    _data = data;
}

void Buffer::clear_data() {
    _data.clear();
}

void Buffer::sleep_until_notified(unique_lock<mutex>& ul) {
    _cv.wait(ul);
}

unique_lock<mutex> Buffer::lock() {
    return unique_lock<mutex> (_mtx);
}

void Buffer::signal() {
    _cv.notify_one();
}