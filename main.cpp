#include "Book.h"
#include "UI.h"
#include <memory>
#include"Serializer.h"
#include"Deserializer.h"
#include"Parser.h"
#include"ManagerCmdlet.h"



using params = std::map<std::string, std::string>;
using cmdlet = std::pair<std::string, params>;
int main()
{

	ConsoleInerface::showCursor();
	std::string str;
	std::getline(std::cin, str);
	auto test = ParserСmdlet();
	cmdlet pure_cmdlet ;
	auto cmdletMngr = ManagerCmdlet::getInstance();
	std::pair<std::string, std::map<std::string, std::string>> res;
	try
	{ 
		res = test.Parse(str); 
		pure_cmdlet = cmdletMngr->cmdltCheck(res);

	}
	catch (CommandError ex) { std::cout << ex.what() << std::endl; }
	
	
	auto deser = Deserializer::getInstance();
	auto deserFunc = [](const nlohmann::json& j) -> std::shared_ptr<Seller>
		{
			auto book = Book::getInstance();
			unsigned long value = 0;
			if (j["office"].is_number_unsigned()) { value = j["office"].get<unsigned long>(); }
			std::shared_ptr<Office> off = book->getOffice(value);
			auto seller = Seller::Builder(j, off).build();
			return std::shared_ptr<Seller>(seller);
		};

	auto book = Book::getInstance();
	auto of1 = std::make_shared<Office>("Halva", "c.Erevan, Hachaturyan str., b.21, Armenia");
	auto of2 = std::make_shared<Office>("Brecel", "c.Berlin, Spitelmarkt str. b. 3, Germany");
	book->addOffice(of1);
	book->addOffice(of2);
	of1.reset();
	of2.reset();
	try
	{
		auto sellers = deser->DeserObj<Seller>("sellers.txt", deserFunc);
		auto book = Book::getInstance();
		for(auto sel : sellers)
		{
			book->addWorker(sel);
		}
	}
	catch (std::ios_base::failure ex)
	{
		std::cout << ex.what() << std::endl;
	}
	

	/*auto sup_b = Supporter::Builder("Ivan", "Petrov").build();
	auto sel_b = Seller::Builder("Mark", "Vazovski")
		.setPhone("+79111787113", "Mobile")
		.setSalesRegion("Russia")
		.setProductSpecialty("VAC")
		.setOffice(of1)
		.build();
	
	auto dev_b = Developer::Builder("Anton", "Trofimov").build();
	

	
	book->addWorker(sup_b);
	book->addWorker(sel_b);
	book->addWorker(dev_b);*/


	

	


	ConsoleInerface UI;
	
	UI.showTable<Worker>(book->getWorkers(), 
		[](std::shared_ptr<Worker> w_ptr) ->std::vector<std::string> {return w_ptr->getShortColums(); },
		[](std::shared_ptr<Worker> w_ptr) ->std::vector<std::string> {return w_ptr->getShortInfo(); });
	UI.showTable<Developer>(book->getConcreteWorkers<Developer>(),
		[](std::shared_ptr<Developer> w_ptr) ->std::vector<std::string> {return w_ptr->getColums(); },
		[](std::shared_ptr<Developer> w_ptr) ->std::vector<std::string> {return w_ptr->getFullInfo(); });
	UI.showTable<Supporter>(book->getConcreteWorkers<Supporter>(),
		[](std::shared_ptr<Supporter> w_ptr) ->std::vector<std::string> {return w_ptr->getColums(); },
		[](std::shared_ptr<Supporter> w_ptr) ->std::vector<std::string> {return w_ptr->getFullInfo(); });
	UI.showTable<Seller>(book->getConcreteWorkers<Seller>(),
		[](std::shared_ptr<Seller> w_ptr) ->std::vector<std::string> {return w_ptr->getColums(); },
		[](std::shared_ptr<Seller> w_ptr) ->std::vector<std::string> {return w_ptr->getFullInfo(); });
	UI.showTable<Office>(book->getOffices(),
		[](std::shared_ptr<Office> o_ptr) ->std::vector<std::string> {return o_ptr->getColums(); },
		[](std::shared_ptr<Office> o_ptr) ->std::vector<std::string> {return o_ptr->getInfo(); });

	


	
	

	std::cout << "Delete Erevan office!" << book->removeOffice(1) << std::endl;

	UI.showTable<Seller>(book->getConcreteWorkers<Seller>(),
		[](std::shared_ptr<Seller> w_ptr) ->std::vector<std::string> {return w_ptr->getColums(); },
		[](std::shared_ptr<Seller> w_ptr) ->std::vector<std::string> {return w_ptr->getFullInfo(); });


	Serializer* ser = Serializer::getInstance();
	auto serFunc = [](const Seller& obj, nlohmann::json& j) {j = obj; };
	ser->SerObjColl<Seller>(book->getConcreteWorkers<Seller>(), "sellers.txt", serFunc);


	
	return 0;
}