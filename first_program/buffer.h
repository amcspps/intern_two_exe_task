#pragma once
#include <mutex>
#include <condition_variable>
#include <string>
class Buffer {
public:

    Buffer() = default;
    Buffer(const Buffer& buffer) = delete;
    Buffer& operator= (const Buffer&) = delete;

    std::string get_data();
    void set_data(std::string data);
    void clear_data();
    void sleep_until_notified (std::unique_lock<std::mutex>& ul);
    void signal();
    std::unique_lock<std::mutex> lock();
private:
std::mutex _mtx;
std::condition_variable _cv;
std::string _data;
};