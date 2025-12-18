#include "Deserializer.h"

template <class T>
std::vector<std::shared_ptr<T>> Deserializer::loadObjs(std::string file_path, std::function<std::shared_ptr<T>(const nlohmann::json&)> deserFunc, std::vector<DeserializingError>* errors)
{
	std::ifstream fin;
	fin.open(file_path);
	if (!fin)
	{
		std::string mes = std::format("Unable to load saved data. Failed to open file \"{}\" for reading. You can ignore this message if this is the first time you are opening the application.", file_path);
		throw std::ios_base::failure(mes);
	}
	std::string line;
	std::vector<std::shared_ptr<T>> res;
	while (std::getline(fin, line))
	{
		try
		{
			auto j = nlohmann::json::parse(line);
			res.push_back(deserFunc(j));
		}
		catch (nlohmann::json::parse_error ex)
		{
			if (errors)
			{
				std::string mes = std::format("Failed deserilize an object from \"{}\".", file_path);
				mes += ex.what();
				errors->push_back(DeserializingError(mes));
			}
		}
	}
	return res;
}

template <WorkerDerived T>
void Deserializer::loadWorkersToBook(const std::string file_path, std::function<std::shared_ptr<T>(const nlohmann::json&)> deserFunc, std::vector<DeserializingError>* errors)
{

	auto book = Book::getInstance();
	auto ObjList = loadObjs<T>(file_path, deserFunc, errors);
	for (auto obj : ObjList)
	{
		book->addWorker(obj);
	}
}

void Deserializer::loadOfficesToBook(const std::string file_path, std::function<std::shared_ptr<Office>(const nlohmann::json&)> deserFunc, std::vector<DeserializingError>* errors)
{

	auto book = Book::getInstance();
	auto ObjList = loadObjs<Office>(file_path, deserFunc, errors);
	for (auto obj : ObjList)
	{
		book->addOffice(obj);
	}
}

Deserializer* Deserializer::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Deserializer();
	}
	return instance;
}

void Deserializer::Load()
{
	std::vector<DeserializingError> errors;

	loadOfficesToBook(Office::Path,
		[](const nlohmann::json& j) {return std::make_shared<Office>(j); },
		&errors);

	loadWorkersToBook<Seller>(Seller::Path,
		&deserEmploeeFunc<Seller>,
		&errors);

	loadWorkersToBook<Developer>(Developer::Path,
		&deserEmploeeFunc<Developer>,
		&errors);

	loadWorkersToBook<Supporter>(Supporter::Path,
		&deserEmploeeFunc<Supporter>,
		&errors);

	auto book = Book::getInstance();
	book->syncId();

	if (!errors.empty()) throw errors;

}

template <class T>
std::shared_ptr<T> deserEmploeeFunc(const nlohmann::json& j)
{
	auto book = Book::getInstance();
	unsigned long value = 0;
	if (j["office"].is_number_unsigned()) { value = j["office"].get<unsigned long>(); }
	std::shared_ptr<Office> off = book->getOffice(value);
	auto emploee = T::Builder(j, off).build();
	return std::shared_ptr<T>(emploee);
};

