#pragma once
#include "Worker.h"
class Developer : public Worker
{
	std::string programming_language = "Unknown";
	std::string level = "Unknown";
	Developer(const Developer::Builder b) : Worker(b) {}
public:
	class Builder : public Worker::Builder
	{
		std::shared_ptr<Developer> developer;
	public:
		Builder(std::string name, std::string last_name) : Worker::Builder(name, last_name)
		{
			setPosition("Developer");
			Developer* temp_ptr = new Developer(*this);
			developer = std::shared_ptr<Developer>(temp_ptr);
		}
		~Builder() {};
		Builder& reset(std::string name, std::string last_name) override
		{
			Worker::Builder::reset(name, last_name);
			Developer* temp_ptr = new Developer(*this);
			developer = std::shared_ptr<Developer>(temp_ptr);
			return *this;
		}
		Builder& setProgrammingLanguage(std::string lang)
		{
			developer->programming_language = lang;
			return *this;
		}
		Builder& setLevel(std::string lvl)
		{
			developer->level = lvl;
			return *this;
		}
		std::shared_ptr<Developer> build()
		{
			auto temp = developer;
			Developer* temp_ptr = new Developer(*this);
			developer = std::shared_ptr<Developer>(temp_ptr);
			return temp;
		}
		Builder& setPhone(std::string Phone, std::string Type = "Unknown") override
		{
			Worker::Builder::setPhone(Phone, Type);
			return *this;
		}
		Builder& setOffice(std::shared_ptr<Office> off) override
		{
			Worker::Builder::setOffice(off);
			return *this;
		}
		friend class Developer;
	};
	friend class Builder;

	void toJSON(nlohmann::json& j) const override
	{
		Worker::toJSON(j);
		j["programming_language"] = programming_language;
		j["level"] = level;
	}

	std::vector<std::string> getFullInfo() const override
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

	std::vector<std::string> getColums() const override
	{
		return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " Programming Language ", " Level ", " Office Name ", " Office Address ", " ID " };
	}
};
