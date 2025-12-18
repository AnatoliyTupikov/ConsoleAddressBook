#pragma once
#include"ManagerCmdlet.h"


ManagerCmdlet::ManagerCmdlet()
{
}

ManagerCmdlet::~ManagerCmdlet()
{
}

ManagerCmdlet* ManagerCmdlet::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ManagerCmdlet();
	}
	return instance;
}

void ManagerCmdlet::setExitLogic(std::function<void()> exit_func)
{
	auto Cmdlet = &pool_cmdlets.at("exit");
	Cmdlet->handler = [exit_func](const std::map<std::string, std::string>&) {exit_func();};
}

void ManagerCmdlet::Execute(const pair_cmdlet cmdlet_pair)
{
	auto pure_cmdlet_obj = buildCmdletStruct(cmdlet_pair);
	pure_cmdlet_obj.handler(pure_cmdlet_obj.parameters);

}

Cmdlet ManagerCmdlet::buildCmdletStruct(const pair_cmdlet cmdlet_pair)
{
	 
	auto cmdlet_it = pool_cmdlets.find(cmdlet_pair.first);

	if (cmdlet_it == pool_cmdlets.cend())
	{
		std::string mes = std::format("\"{}\" commandlet is unknown.", cmdlet_pair.first);
		throw CommandError(mes);
	}

	std::string error_mes = "";

	auto income_params = cmdlet_pair.second;

	Cmdlet CmdletForm = cmdlet_it->second;

	CmdletForm.replacePlaceholder(pool_cmdlets.at(base_params_ident));
	

	auto& form_params = CmdletForm.parameters;
	if(!form_params.empty())
	{
		for (auto& form_param : form_params)
		{
			std::string form_parameter_name = form_param.first;
			std::string form_parameter_val = form_param.second;			

			auto it = income_params.find(form_parameter_name);
			if (it == income_params.cend())
			{
				if (form_parameter_val.empty()) error_mes += std::format("\"{}\" parameter for \"{}\" commandlet is required. But isn't specified!", form_param.first, cmdlet_pair.first);
				continue;
			}
			form_param.second = it->second;
			income_params.erase(it);
		}
	}
	

	if(!income_params.empty())
	{
		for(auto excess_param : income_params)
		{
			error_mes += std::format("\"{}\" commandlet doesn't have \"{}\" parameter.", cmdlet_pair.first, excess_param.first);
		}		
	}

	if (!error_mes.empty()) throw CommandError(error_mes);

	return CmdletForm;		
}




