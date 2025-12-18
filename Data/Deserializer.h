#pragma once
#include <fstream>
#include <utility>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <memory>
#include "Book.h"
#include "../Exceps/DeserializingError.h"
#include <concepts>

template <class T>
std::shared_ptr<T> deserEmploeeFunc(const nlohmann::json& j);

template <typename T>
concept WorkerDerived = std::is_base_of_v<Worker, T>;

class Deserializer
{	
	static inline Deserializer* instance = nullptr;	

	template <class T>
	std::vector<std::shared_ptr<T>> loadObjs(std::string file_path, std::function<std::shared_ptr<T>(const nlohmann::json&)> deserFunc, std::vector<DeserializingError>* errors = nullptr);

	template <WorkerDerived T>
	void loadWorkersToBook(std::string file_path, std::function<std::shared_ptr<T>(const nlohmann::json&)> deserFunc, std::vector<DeserializingError>* errors = nullptr);

	void loadOfficesToBook(std::string file_path, std::function<std::shared_ptr<Office>(const nlohmann::json&)> deserFunc, std::vector<DeserializingError>* errors = nullptr);

protected:
	Deserializer() {};

public:
	static Deserializer* getInstance();	
	void Load();
	~Deserializer() {};
};








