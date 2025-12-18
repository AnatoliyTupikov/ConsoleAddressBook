#pragma once
#include <string>
#include <map>
#include <optional>
#include <functional>


using CmdletHandler = std::function<void(const std::map<std::string, std::string>&)>;
 struct Cmdlet
 {
	 std::string name;
	 std::map<std::string, std::string> parameters;
	 CmdletHandler handler;

	 

	 bool findParameter(std::string param_name,std::string* value_case = nullptr )
	 {
		 auto it = parameters.find(param_name);
		 bool is_found = it != parameters.end();
		 std::string value = is_found ? parameters.at(param_name) : "";
		 if (value_case) *value_case = value;
		 return is_found;
	 }


	 void replacePlaceholder(const Cmdlet& base_cmdlt)
	 {
		 		 
		 if (!this->findParameter(base_cmdlt.name)) return;
		 auto base_params = base_cmdlt.parameters;
		 for (auto base_param : base_params)
		 {
			 this->parameters.insert(base_param);
		 }
		 this->parameters.erase(base_cmdlt.name);

	 }

 };