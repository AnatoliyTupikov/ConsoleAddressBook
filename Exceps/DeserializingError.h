#pragma once
#include<string>

class DeserializingError
{
	std::string message;
public:
	DeserializingError(const std::string& msg) : message(msg) {};
	const char* what() const { return message.c_str(); };
};


