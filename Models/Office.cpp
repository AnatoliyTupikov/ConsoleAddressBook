#include "Office.h"

Office::Office(std::string office_name, std::string office_address) : name(office_name), address(office_address), id(++id_sequence) {}
Office::Office(const nlohmann::json& j)
{
	try
	{
		if (j.at("id").is_number_unsigned()) { id = j.at("id").get<unsigned long>(); }
		else id = ++id_sequence;
		name = j.at("name");
		address = j.at("address");
	}
	catch (nlohmann::json::out_of_range ex)
	{
		std::string mess = "Wrong parsed Data from the file, the parameter is missing";
		mess += "\n";
		mess += ex.what();
		throw DeserializingError(mess);
	}
}

std::vector<std::string> Office::getColums()
{
	return { " Office Name ", " Office Address ", " Office ID " };
}

std::vector<std::string> Office::getInfo() const
{
	std::vector<std::string> info;
	info.push_back(name);
	info.push_back(address);
	info.push_back(std::to_string(id));
	return info;
}

void Office::toJSON(nlohmann::json& j) const
{
	j = nlohmann::json
	{

		{"name", name},
		{"address", address},
		{"id", id }
	};

}