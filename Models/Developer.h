#pragma once
#include "Worker.h"
class Developer : public Worker
{	
	std::string programming_language = "Unknown";
	std::string level = "Unknown";

	class Builder;
	Developer(const Developer::Builder& b) : Worker(b) 
	{
		programming_language = b.programming_language;
		level = b.level;
	}

public:
	const static inline std::string Path = "DataStore/developers.txt";

	//Builer class===========================
	class Builder : public Worker::Builder
	{
		std::string programming_language = "Unknown";
		std::string level = "Unknown";

	public:
		Builder(std::string name, std::string last_name);
		Builder(const nlohmann::json& j, std::shared_ptr<Office> off = nullptr);
		~Builder() {};
		Builder& reset(std::string name, std::string last_name) override;
		Builder& setProgrammingLanguage(std::string lang);
		Builder& setLevel(std::string lvl);
		std::shared_ptr<Developer> build();
		Builder& setPhone(std::string Phone, std::string Type = "Unknown") override;
		Builder& setOffice(std::shared_ptr<Office> off) override;

		friend class Developer;
	};	
	//Builer class end===========================

	void toJSON(nlohmann::json& j) const override;
	std::vector<std::string> getFullInfo() const override;
	static std::vector<std::string> getColums();
};
