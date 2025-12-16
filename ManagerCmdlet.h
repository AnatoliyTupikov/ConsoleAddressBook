#pragma once
#include <map>
#include <string>
using params = std::map<std::string, std::string>;
using cmdlet = std::pair<std::string, params>;
using cmdltDict = std::map<std::string, params>;
class ManagerCmdlet
{
	static inline ManagerCmdlet* instance = nullptr;
	const std::string base_params_ident = "+=.a;lsd&a["; //for getting list of base params
	//params with empty string are required
	const cmdltDict pool_cmdlets = 
	{		

		{base_params_ident, //not a cmdlt, technical data for base param chek
		{
			{"n",""},
			{"ln",""},
			{"ph","-"},
			{"phtype","Mobile"},			
			{"o","0"}
		}},

		{"get-help",{{}}},
		
		{"add-seller",
		{
			{base_params_ident,""},
			{"sr","Not Assigned"},
			{"ps","Not Assigned"}
		}},

		{"add-dev",
		{
			{base_params_ident,""},
			{"pl","Unknown"},
			{"lvl","Unknown"}
		}},

		{"add-supprt",
		{
			{base_params_ident,""},
			{"sl","Unknown"}			
		}},

		{"remove-worker",
		{
			{"id",""} 
		}},

		{"add-office",
		{
			{"n",""},
			{"adr",""}
		}},

		{"remove-office",
		{
			{"id",""} 
		}},

		{"get-workers",{{}}},

		{"get-sellers",{{}}},

		{"get-devs",{{}}},

		{"get-supprts",{{}}},

		{"get-offices",{{}}},

		{"exit",{{}}}

	};
public:	

	static ManagerCmdlet* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new ManagerCmdlet();
		}
		return instance;
	}
	~ManagerCmdlet();

	
	cmdlet cmdltCheck(cmdlet cmdlet_obj);
	cmdlet getCmdletForm(const std::string& cmdlet_name, const params& par) const;

	//std::pair<std::string, params> getCmdletForm(const std::string& cmdlet_name, const std::map<std::string, std::string>& par) const;
	//std::pair<std::string, std::map<std::string, std::string>> cmdltCheck(std::pair<std::string, std::map<std::string, std::string>> cmdlt);
	//std::pair<std::string, params> getCmdletForm(const std::string& cmdlet_name, const std::map<std::string, std::string>& par) const;


protected:
	ManagerCmdlet();
};
