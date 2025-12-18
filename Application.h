#pragma once
#include "Interface/ConsoleInterface.h"
#include "Data/All.h"
#include"CmdLet/ManagerCmdlet.h"
#include <filesystem>
namespace fs = std::filesystem;
using UI = ConsoleInterface;

class Application
{
	Book* book;
	Serializer* saver;
	Deserializer* loader;
	ManagerCmdlet* CMDm;
	
	bool is_running = false;
	static inline Application* instance = nullptr;
	Application()
	{
		book = Book::getInstance();
		saver = Serializer::getInstance();
		loader = Deserializer::getInstance();
		CMDm = ManagerCmdlet::getInstance();
		CMDm->setExitLogic([this]() {this->Exit(); });
	}

	void ensureFileExists(const std::string& file_path) {
		if (!fs::exists(file_path)) {
			std::ofstream fout(file_path); // создаем файл
			if (!fout) {
				throw std::ios_base::failure("Failed to create file: " + file_path);
			}
			fout.close();		
		}		
	}

public:
	static Application* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Application();
		}
		return instance;
	}

	void Start()
	{
		
		try
		{
			ensureFileExists(Seller::Path);
			ensureFileExists(Developer::Path);
			ensureFileExists(Supporter::Path);
			ensureFileExists(Office::Path);
			loader->Load();
		}
		catch (std::ios_base::failure ex) { UI::showError(ex.what()); }
		catch (std::vector<DeserializingError> errors) { for (auto err : errors) { ConsoleInterface::showError(err.what()); } }
		catch (DeserializingError ex) { ConsoleInterface::showError(ex.what()); }
		catch (nlohmann::json::parse_error ex) { ConsoleInterface::showError(ex.what()); }
		catch (std::exception ex) { ConsoleInterface::showError(ex.what()); }

		UI::showMessage("Welcome to EmploeeBook App.!");
		UI::showMessage("Only English symbols!");
		UI::showMessage("For Cmdlets information use \"Get-Hepl\"");

		is_running = true;
		while(is_running)
		{
			try 
			{
				auto cmdlet_pair = UI::requestCommand();
				if (cmdlet_pair.first.empty()) continue;

				CMDm->Execute(cmdlet_pair);
			}
			catch (std::ios_base::failure ex) { UI::showError(ex.what()); }
			catch (std::vector<DeserializingError> errors) { for (auto err : errors) { ConsoleInterface::showError(err.what()); } }
			catch (DeserializingError ex) { ConsoleInterface::showError(ex.what()); }
			catch (nlohmann::json::parse_error ex) { ConsoleInterface::showError(ex.what()); }
			catch (CommandError ex) { ConsoleInterface::showError(ex.what()); }
			catch (std::exception ex) { ConsoleInterface::showError(ex.what()); }
		}

	}

	void Exit()
	{
		auto answer = UI::requestString("Are you sure you want to exit? (y/n) ");
		answer = ParserCmdlet::toLowerOneWord(answer);

		if(answer == "y" || answer == "yes")
		{
			try
			{
				saver->Save();
				is_running = false;
			}
			catch (std::ios_base::failure ex) 
			{ 
				UI::showError("Can't save the changes by the next reason:\n");
				UI::showError(ex.what()); 
				auto ws = UI::requestString("Exit without saving changes? (y/n) ");
				ws = ParserCmdlet::toLowerOneWord(ws);
				if (ws == "y" || ws == "yes") is_running = false;
			}	
			
		}
	}
	

};

