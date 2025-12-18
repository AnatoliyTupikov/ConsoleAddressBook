#include "Developer.h"


Developer::Builder::Builder(std::string name, std::string last_name) : Worker::Builder(name, last_name)
{
	setPosition("Developer");
}

Developer::Builder::Builder(const nlohmann::json& j, std::shared_ptr<Office> off) : Worker::Builder(j, off)
{
	try
	{
		programming_language = j.at("programming_language");
		level = j.at("level");
	}
	catch (nlohmann::json::out_of_range ex)
	{
		std::string mess = fromJsonError;
		mess += "\n";
		mess += ex.what();
		throw DeserializingError(mess);
	}
}

Developer::Builder& Developer::Builder::reset(std::string name, std::string last_name)
{
	Worker::Builder::reset(name, last_name);
	programming_language = "Unknown";
	level = "Unknown";
	return *this;
}

Developer::Builder& Developer::Builder::setProgrammingLanguage(std::string lang)
{
	programming_language = lang;
	return *this;
}

Developer::Builder& Developer::Builder::setLevel(std::string lvl)
{
	level = lvl;
	return *this;
}

std::shared_ptr<Developer> Developer::Builder::build()
{
	Developer* temp_ptr = new Developer(*this);
	auto res = std::shared_ptr<Developer>(temp_ptr);
	return res;
}
Developer::Builder& Developer::Builder::setPhone(std::string Phone, std::string Type)
{
	Worker::Builder::setPhone(Phone, Type);
	return *this;
}

Developer::Builder& Developer::Builder::setOffice(std::shared_ptr<Office> off)
{
	Worker::Builder::setOffice(off);
	return *this;
}

void Developer::toJSON(nlohmann::json& j) const
{
	Worker::toJSON(j);
	j["programming_language"] = programming_language;
	j["level"] = level;
}

std::vector<std::string> Developer::getFullInfo() const
{
	std::vector<std::string> info;
	info.push_back(name);
	info.push_back(last_name);
	info.push_back(phone.getPhone());
	info.push_back(phone.getType());
	info.push_back(position);
	info.push_back(programming_language);
	info.push_back(level);
	info.push_back(office.lock() ? office.lock()->getName() : "No Office Assigned");
	info.push_back(office.lock() ? office.lock()->getAddress() : "-");
	info.push_back(std::to_string(id));
	return info;
}

std::vector<std::string> Developer::getColums()
{
	return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " Programming Language ", " Level ", " Office Name ", " Office Address ", " ID " };
}