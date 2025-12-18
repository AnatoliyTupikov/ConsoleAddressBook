#pragma once
#include <map>
#include <string>
#include <memory>
#include "Cmdlet.h"
#include <iostream>
#include <format>
#include "../Interface/ConsoleInterface.h"
#include "../Interface/ParserCmdlet.h"
#include "../Models/All.h"
#include "../Data/Book.h"
#include "../Data/Serializer.h"
#include"../Exceps/CommandError.h"


namespace CmdletLogic
{
	void add_seller_handler(const std::map<std::string, std::string>& params);
	void add_dev_handler(const std::map<std::string, std::string>& params);
	void add_support_handler(const std::map<std::string, std::string>& params);
	void remove_employee_handler(const std::map<std::string, std::string>& params);
	void add_office_handler(const std::map<std::string, std::string>& params);
	void remove_office_handler(const std::map<std::string, std::string>& params);
	void get_help_handler(const std::map<std::string, std::string>& params);
	void get_all_handler(const std::map<std::string, std::string>& params);
	void get_sellers_handler(const std::map<std::string, std::string>& params);
	void get_devs_handler(const std::map<std::string, std::string>& params);
	void get_supports_handler(const std::map<std::string, std::string>& params);
	void get_offices_handler(const std::map<std::string, std::string>& params);
	void exit_placeholder_handler(const std::map<std::string, std::string>& params);
}




using params = std::map<std::string, std::string>;
using pair_cmdlet = std::pair<std::string, params>;
using cmdltDict = std::map<std::string, Cmdlet>;

class ManagerCmdlet
{
	static inline ManagerCmdlet* instance = nullptr;
	
	const std::string base_params_ident = "+=.a;lsd&a["; //for getting list of base params
	 cmdltDict pool_cmdlets =
	{
		{ base_params_ident,
		Cmdlet
		{
			base_params_ident,
			{
				{"n",""},
				{"ln",""},
				{"ph","-"},
				{"phtype","mobile"},
				{"o","0"}
			}
		}},

		{ "add-seller",
		Cmdlet
		{
			"add-seller",
			{
				{base_params_ident,""},
				{"sr","not assigned"},
				{"ps","not assigned"}
			},
			CmdletLogic::add_seller_handler
		}},

		{ "add-dev",
		Cmdlet
		{
			"add-dev",
			{
				{base_params_ident,""},
				{"plang","unknown"},
				{"lvl","unknown"}
			},
			CmdletLogic::add_dev_handler
		}},

		{ "add-support",
		Cmdlet
		{
			"add-suppоrt",
			{
				{base_params_ident,""},
				{"sl","unknown"}	
			},
			CmdletLogic::add_support_handler
		}},

		{ "remove-employee",
		Cmdlet
		{
			"remove-employee",
			{
				{"id",""}
			},
			CmdletLogic::remove_employee_handler
		}},

		{ "add-office",
		Cmdlet
		{
			"add-office",
			{
				{"n",""},
				{"adr",""}
			},
			CmdletLogic::add_office_handler
		}},

		{ "remove-office",
		Cmdlet
		{
			"remove-office",
			{
				{"id",""}
			},
			CmdletLogic::remove_office_handler
		}},

		{ "get-help",
		Cmdlet
		{
			"get-help",
			{},
			CmdletLogic::get_help_handler
		}},

		{ "get-all",
		Cmdlet
		{
			"get-all",
			{},
			CmdletLogic::get_all_handler
		}},

		{ "get-sellers",
		Cmdlet
		{
			"get-sellers",
			{},
			CmdletLogic::get_sellers_handler
		}},

		{ "get-devs",
		Cmdlet
		{
			"get-devs",
			{},
			CmdletLogic::get_devs_handler
		} },

		{ "get-supports",
		Cmdlet
		{
			"get-supports",
			{},
			CmdletLogic::get_supports_handler
		}},

		{ "get-offices",
		Cmdlet
		{
			"get-offices",
			{},
			CmdletLogic::get_offices_handler
		}},

		{ "exit",
		Cmdlet
		{
			"exit",
			{},
			CmdletLogic::exit_placeholder_handler
		} }
	};
	Cmdlet buildCmdletStruct(const pair_cmdlet cmdlet_pair);
public:	

	static ManagerCmdlet* getInstance();
	void setExitLogic(std::function<void()> exit_func);
	void Execute(const pair_cmdlet cmdlet_pair);
	~ManagerCmdlet();
	

protected:
	ManagerCmdlet();
	
};
