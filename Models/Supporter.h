#pragma once
#include "Worker.h"
#include <string>
class Supporter : public Worker
{
	
	std::string support_line = "Unknown";

	class Builder;
	Supporter(const Supporter::Builder& b) : Worker(b) 
	{
		support_line = b.support_line;
	}

public:

	const static inline std::string Path = "DataStore/supporters.txt";

	class Builder : public Worker::Builder
	{
		std::string support_line = "Unknown";
		
	public:
		Builder(std::string name, std::string last_name) : Worker::Builder(name, last_name)
		{
			setPosition("Support");
			
		}
		Builder(const nlohmann::json& j, std::shared_ptr<Office> off = nullptr) : Worker::Builder(j, off)
		{
			try
			{
				support_line = j.at("support_line");				
			}
			catch (nlohmann::json::out_of_range ex)
			{
				std::string mess = fromJsonError;
				mess += "\n";
				mess += ex.what();
				throw DeserializingError(mess);
			}
		}
		~Builder() {};
		Builder& reset(std::string name, std::string last_name) override
		{
			Worker::Builder::reset(name, last_name);
			support_line = "Unknown";
			return *this;
		}
		Builder& setSupportLine(std::string line)
		{
			support_line = line;
			return *this;
		}		
		std::shared_ptr<Supporter> build()
		{
			
			Supporter* temp_ptr = new Supporter(*this);
			auto res = std::shared_ptr<Supporter>(temp_ptr);
			return res;
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

	static std::vector<std::string> getColums()
	{
		return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " Support Line ", " Office Name ", " Office Address ", " ID " };
	}
};
