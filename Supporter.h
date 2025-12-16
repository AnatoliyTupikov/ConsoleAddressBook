#pragma once
#include "Worker.h"
class Supporter : public Worker
{
	std::string support_line = "Unknown";
	
	Supporter(const Supporter::Builder b) : Worker(b) {}
public:
	class Builder : public Worker::Builder
	{
		std::shared_ptr<Supporter> supporter;
	public:
		Builder(std::string name, std::string last_name) : Worker::Builder(name, last_name)
		{
			setPosition("Support");
			Supporter* temp_ptr = new Supporter(*this);
			supporter = std::shared_ptr<Supporter>(temp_ptr);
		}
		~Builder() {};
		Builder& reset(std::string name, std::string last_name) override
		{
			Worker::Builder::reset(name, last_name);
			Supporter* temp_ptr = new Supporter(*this);
			supporter = std::shared_ptr<Supporter>(temp_ptr);
			return *this;
		}
		Builder& setSupportLine(std::string line)
		{
			supporter->support_line = line;
			return *this;
		}		
		std::shared_ptr<Supporter> build()
		{
			auto temp = supporter;
			Supporter* temp_ptr = new Supporter(*this);
			supporter = std::shared_ptr<Supporter>(temp_ptr);
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
		friend class Supporter;
	};

	friend class Builder;

	void toJSON(nlohmann::json& j) const override
	{
		Worker::toJSON(j);
		j["support_line"] = support_line;		
	}

	std::vector<std::string> getFullInfo() const override
	{

		std::vector<std::string> info;
		info.push_back(name);
		info.push_back(last_name);
		info.push_back(phone.getPhone());
		info.push_back(phone.getType());
		info.push_back(position);
		info.push_back(support_line);
		info.push_back(office.lock() ? office.lock()->getName() : "No Office Assigned");
		info.push_back(office.lock() ? office.lock()->getAddress() : "-");
		info.push_back(std::to_string(id));
		return info;
	}

	std::vector<std::string> getColums() const override
	{
		return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " Support Line ", " Office Name ", " Office Address ", " ID " };
	}
};
