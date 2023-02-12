#include "reader.h"
#include <algorithm>
#include <numeric>

using namespace std;

string Reader::read_data() {
    string tmpstr;
    cin >> tmpstr;
    return tmpstr;
}

bool Reader::check(string& tmpstr) {
    return tmpstr.length() <= 64 && std::all_of(tmpstr.begin(), tmpstr.end(), [](char c) {return std::isdigit(c);});
}

string Reader::sort_replace(string& tmpstr) {
    sort(tmpstr.begin(),tmpstr.end(), greater<char>());
    string ret = accumulate(tmpstr.begin(),tmpstr.end(),string{""},[](string left, char r) {
        if (r%2 == 0) {
            return left + "KB";
        } else {
            return left + r;
        }
    });
    return ret;
}

void Reader::run(){
    while(true) {
        string input = read_data();
        if(!check(input)) {
            cout << "input string is invalid, please input another" << endl;
        }
        else {
            string sorted = sort_replace(input);
            auto lock = _buffer.lock();
            _buffer.set_data(sorted);
            lock.unlock();
            _buffer.signal();
        }

    }
}