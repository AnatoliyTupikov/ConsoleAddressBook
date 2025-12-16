#pragma once
#include<string>

class CommandError {
    std::string message;
public:
    CommandError(const std::string& msg) : message(msg) {}
    const char* what() const { return message.c_str(); }
};