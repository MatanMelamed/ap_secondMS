#ifndef AP_SECONDMS_MYEXCEPTION_H
#define AP_SECONDMS_MYEXCEPTION_H

#include <iostream>
#include <string>

class MyException {

    std::string _message;

    MyException() = default;;

public:
    explicit MyException(const std::string &message) {
        this->_message = message;
    }

    std::string get() { return _message; }
};

#endif
