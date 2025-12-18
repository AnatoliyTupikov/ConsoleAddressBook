#pragma once
#include <string>
class Telephone 
{
	std::string phone;
	std::string type;
public:
	Telephone(std::string number, std::string type) : phone(number), type(type) {}
	Telephone() : Telephone("-", "Unknown") {}
	Telephone(std::string number) : Telephone(number, "Unknown") {}

	void setPhone(std::string number) { phone = number; }
	std::string getPhone() const { return phone; } 
	void setType(std::string t) { type = t; }	
	std::string getType() const { return type; }
	
};
