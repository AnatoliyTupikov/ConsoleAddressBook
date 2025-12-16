#pragma once
#include <fstream>
#include "Book.h"
#include <utility>
#include <nlohmann/json.hpp>
#include <typeinfo>

class Serializer
{

	static inline Serializer* instance = nullptr;
public:
	
	~Serializer();

	template <class T>
	void SerObjColl(std::vector<std::shared_ptr<T>> list, std::string file_path, void (*serFunc)(const T& obj, nlohmann::json& j))
	{	

		std::ofstream fout;
		fout.open(file_path);

		if (!fout) 
		{ 
			std::string mes = std::format("Failed to open output file  \"{}\" for saving!", file_path);
			throw std::ios_base::failure(mes); 
		}

		for (auto el : list)
		{
			
			auto j = nlohmann::json();
			serFunc(*el, j);
			fout << j << std::endl;

		}
	}

	

	static Serializer* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Serializer();
		}
		return instance;
	}

protected:
	Serializer();
};



Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}
