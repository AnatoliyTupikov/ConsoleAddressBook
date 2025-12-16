#pragma once
#include <string>
#include <vector>

class Office
{
	static inline unsigned long id_sequence = 0;
	unsigned long id;
	std::string name;
	std::string address;
public:
	Office(std::string office_name, std::string office_address) : name(office_name), address(office_address), id(++id_sequence) {}
	static unsigned long getIdSequence() { return id_sequence; }
	static void setIdSequence(unsigned long new_sequence) { id_sequence = new_sequence; }
	std::string getName() const { return name; }
	std::string getAddress() const { return address; }
	unsigned long getId() const { return id; }

	std::vector<std::string> getColums() const
	{
		return { " Office Name ", " Office Address ", " Office ID " };
	}
	std::vector<std::string> getInfo() const
	{
		std::vector<std::string> info;
		info.push_back(name);
		info.push_back(address);
		info.push_back(std::to_string(id));
		return info;
	}


};
