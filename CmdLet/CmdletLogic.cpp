#include "ManagerCmdlet.h"

namespace CmdletLogic
{
	auto book = Book::getInstance();
	auto saver = Serializer::getInstance();

	std::shared_ptr<Office> getOfficeFromStr(std::string str_id)
	{
		std::string mes = std::format("\"{}\" is wrong value for office's ID (\"-o\" parameter). It must be integer > 0.", str_id);
		unsigned long id = ParserCmdlet::idFromString(str_id, mes);

		if (id == 0) return nullptr;

		//auto book = Book::getInstance();
		auto off_ptr = book->getOffice(id);
		if (!off_ptr)
		{
			std::string mes = std::format("There is no the office with ID = \"{}\".", id);
			throw CommandError(mes);
		}
		return off_ptr;
	}

	void add_seller_handler(const std::map<std::string, std::string>& params)
	{

		std::string str_id = params.at("o");
		auto office = getOfficeFromStr(str_id);
		
		std::shared_ptr<Seller> new_seller = Seller::Builder(params.at("n"), params.at("ln"))
			.setOffice(office)
			.setPhone(params.at("ph"), params.at("phtype"))
			.setProductSpecialty(params.at("ps"))
			.setSalesRegion(params.at("sr"))
			.build();
		book->addWorker(new_seller);

		saver->saveAddObj<Seller>(new_seller, Seller::Path,
			[](const Seller& obj, nlohmann::json& j) {j = obj; });

		std::string mes = std::format("The seller with Id = \"{}\" was added.", new_seller->getId());
		ConsoleInterface::showMessage(mes);

	}

	void add_dev_handler(const std::map<std::string, std::string>& params)
	{
		std::string str_id = params.at("o");
		auto office = getOfficeFromStr(str_id);

		std::shared_ptr<Developer> new_developer = Developer::Builder(params.at("n"), params.at("ln"))
			.setOffice(office)
			.setPhone(params.at("ph"), params.at("phtype"))
			.setProgrammingLanguage(params.at("pl"))
			.setLevel(params.at("lvl"))
			.build();
		
		book->addWorker(new_developer);

		saver->saveAddObj<Developer>(new_developer, Developer::Path,
			[](const Developer& obj, nlohmann::json& j) {j = obj; });

		std::string mes = std::format("The developer with Id = \"{}\" was added.", new_developer->getId());
		ConsoleInterface::showMessage(mes);
	};
	void add_support_handler(const std::map<std::string, std::string>& params)
	{
		std::string str_id = params.at("o");
		auto office = getOfficeFromStr(str_id);
		
		std::shared_ptr<Supporter> new_supporter = Supporter::Builder(params.at("n"), params.at("ln"))
			.setOffice(office)
			.setPhone(params.at("ph"), params.at("phtype"))
			.setSupportLine(params.at("sl"))
			.build();

		book->addWorker(new_supporter);
		saver->saveAddObj<Supporter>(new_supporter, Supporter::Path,
			[](const Supporter& obj, nlohmann::json& j) {j = obj; });

		std::string mes = std::format("The supporter with Id = \"{}\" was added.", new_supporter->getId());
		ConsoleInterface::showMessage(mes);
	};
	void remove_employee_handler(const std::map<std::string, std::string>& params)
	{
		auto str_id = params.at("id");
		std::string mes = std::format("\"{}\" is wrong value for emploee's ID (\"-id\" parameter). It must be integer > 0.", str_id);
		unsigned long id = ParserCmdlet::idFromString(str_id, mes);
		
		if (!book->removeWorker(id))
		{
			std::string mes = std::format("There is no the emploee with ID = \"{}\".", id);
			throw CommandError(mes);
		}		

		mes = std::format("The emploee with Id = \"{}\" was removed.", str_id);
		ConsoleInterface::showMessage(mes);
	};

	void add_office_handler(const std::map<std::string, std::string>& params)
	{
		Office* temp_ptr = new Office(params.at("n"), params.at("adr"));
		auto off = std::shared_ptr<Office>(temp_ptr);
		
		book->addOffice(off);

		saver->saveAddObj<Office>(off, Office::Path,
			[](const Office& obj, nlohmann::json& j) {obj.toJSON(j); });

		std::string mes = std::format("The office with Id = \"{}\" was added.\n", off->getId());
		ConsoleInterface::showMessage(mes);
	};
	void remove_office_handler(const std::map<std::string, std::string>& params)
	{
		auto str_id = params.at("id");
		std::string mes = std::format("\"{}\" is wrong value for office's ID (\"-id\" parameter). It must be integer > 0.", str_id);
		unsigned long id = ParserCmdlet::idFromString(str_id, mes);
		
		if (!book->removeOffice(id))
		{
			mes = std::format("There is no the office with ID = \"{}\".", id);
			throw CommandError(mes);
		}

		mes = std::format("The office with Id = \"{}\" was removed.", str_id);
		ConsoleInterface::showMessage(mes);
	};

	void get_help_handler(const std::map<std::string, std::string>& params)
	{
		std::string path = "DataStore/get-help.txt";
		std::ifstream fin;
		std::string line;
		fin.open(path);
		if (!fin)
		{
			std::string mes = std::format("Unable to load \"{}\" file.", path);
			throw CommandError(mes);
		}
		while (std::getline(fin, line))
		{
			ConsoleInterface::showMessage(line);
		}
	};

	void get_all_handler(const std::map<std::string, std::string>& params)
	{
		
		ConsoleInterface::showList<Worker>(book->getWorkers(), Worker::getColums(),
			[](std::shared_ptr<Worker> w_ptr) ->std::vector<std::string> {return w_ptr->getShortInfo(); });
	};
	void get_sellers_handler(const std::map<std::string, std::string>& params)
	{
		
		ConsoleInterface::showList<Seller>(book->getConcreteWorkers<Seller>(), Seller::getColums(),
			[](std::shared_ptr<Seller> w_ptr) ->std::vector<std::string> {return w_ptr->getFullInfo(); });
	};
	void get_devs_handler(const std::map<std::string, std::string>& params)
	{
		ConsoleInterface::showList<Developer>(book->getConcreteWorkers<Developer>(), Developer::getColums(),
			[](std::shared_ptr<Developer> w_ptr) ->std::vector<std::string> {return w_ptr->getFullInfo(); });
	};
	void get_supports_handler(const std::map<std::string, std::string>& params)
	{
		
		ConsoleInterface::showList<Supporter>(book->getConcreteWorkers<Supporter>(), Supporter::getColums(),
			[](std::shared_ptr<Supporter> w_ptr) ->std::vector<std::string> {return w_ptr->getFullInfo(); });
	};
	void get_offices_handler(const std::map<std::string, std::string>& params)
	{
		
		ConsoleInterface::showList<Office>(book->getOffices(), Office::getColums(),
			[](std::shared_ptr<Office> o_ptr) ->std::vector<std::string> {return o_ptr->getInfo(); });
	};

	void exit_placeholder_handler(const std::map<std::string, std::string>& params)
	{
		throw CommandError("Exit function wasn't set for \"exit\" command. Use \"setExitLogic\" function for \"ManagerCmdlet\" object.");
	};
}