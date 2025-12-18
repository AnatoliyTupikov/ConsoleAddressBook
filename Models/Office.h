#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../Exceps/DeserializingError.h"

class Office
{	
	static inline unsigned long id_sequence = 0;
	unsigned long id;
	std::string name;
	std::string address;

public:

	const static inline std::string Path = "DataStore/offices.txt";

	Office(std::string office_name, std::string office_address);
	Office(const nlohmann::json& j);

	static unsigned long getIdSequence() { return id_sequence; }
	static void setIdSequence(unsigned long new_sequence) { id_sequence = new_sequence; }
	std::string getName() const { return name; }
	std::string getAddress() const { return address; }
	unsigned long getId() const { return id; }

	static std::vector<std::string> getColums();
	std::vector<std::string> getInfo() const;
	void toJSON(nlohmann::json& j) const;
};

//void to_json(nlohmann::json& j, const Office& w);