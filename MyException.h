#ifndef AP_SECONDMS_MYEXCEPTION_H
#define AP_SECONDMS_MYEXCEPTION_H

#include <iostream>
#include <string>

#define DEF_ERROR -1

int Guard(int check, const std::string &message, int error = DEF_ERROR);

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
