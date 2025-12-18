#pragma once
#include <fstream>
#include <utility>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include "../Models/All.h"
#include"Book.h"

class Serializer
{
	static inline Serializer* instance = nullptr;	

protected:
	Serializer() {};

public:	
	~Serializer() {};	

	static Serializer* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Serializer();
		}
		return instance;
	}

	void Save()
	{
		auto book = Book::getInstance();

		saveRewriteObjs<Seller>(book->getConcreteWorkers<Seller>(), Seller::Path,
			[](const Seller& obj, nlohmann::json& j) {j = obj; });

		saveRewriteObjs<Developer>(book->getConcreteWorkers<Developer>(), Developer::Path,
			[](const Developer& obj, nlohmann::json& j) {j = obj; });

		saveRewriteObjs<Supporter>(book->getConcreteWorkers<Supporter>(), Supporter::Path,
			[](const Supporter& obj, nlohmann::json& j) {j = obj; });

		saveRewriteObjs<Office>(book->getOffices(), Office::Path,
			[](const Office& obj, nlohmann::json& j) {obj.toJSON(j); });
	}

	template <class T>
	void saveRewriteObjs(std::vector<std::shared_ptr<T>> list, std::string file_path, void (*serFunc)(const T& obj, nlohmann::json& j))
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

	template <class T>
	void saveAddObj(std::shared_ptr<T> obj, std::string file_path, void (*serFunc)(const T& obj, nlohmann::json& j))
	{
		std::ofstream fout;
		fout.open(file_path, std::ios::app);
		if (!fout)
		{
			std::string mes = std::format("Failed to open output file  \"{}\" for saving!", file_path);
			throw std::ios_base::failure(mes);
		}

		auto j = nlohmann::json();
		serFunc(*obj, j);
		fout << j << std::endl;
	}

	
};



