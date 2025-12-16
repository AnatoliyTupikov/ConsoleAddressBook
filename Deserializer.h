#pragma once
#include <fstream>
#include "Book.h"
#include <utility>
#include <nlohmann/json.hpp>
#include <stdexcept>

class Deserializer
{
	static inline Deserializer* instance = nullptr;
public:
	
	~Deserializer();

	template <class T>
	std::vector<std::shared_ptr<T>> DeserObj(std::string file_path, std::shared_ptr<T>(*deserFunc)(const nlohmann::json& j))
	{
		auto book = Book::getInstance();
		
		std::ifstream fin;
		fin.open(file_path);
		if (!fin)
		{
			std::string mes = std::format("Failed to open output file  \"{}\" for reading!", file_path);
			throw std::ios_base::failure(mes);
		}
		std::string line;
		std::vector<std::shared_ptr<T>> res;
		while (std::getline(fin, line))
		{
			auto j = nlohmann::json::parse(line);
			res.push_back(deserFunc(j));			
		}
		return res;
	}

	static Deserializer* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Deserializer();
		}
		return instance;
	}

protected:
	Deserializer();
};



Deserializer::Deserializer()
{
}

Deserializer::~Deserializer()
{
}