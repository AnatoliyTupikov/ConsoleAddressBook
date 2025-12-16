#pragma once
#include"ManagerCmdlet.h"
#include"CommandError.h"
#include <format>



ManagerCmdlet::ManagerCmdlet()
{
}

ManagerCmdlet::~ManagerCmdlet()
{
}
using params = std::map<std::string, std::string>;
using cmdlet = std::pair<std::string, params>;
cmdlet ManagerCmdlet::cmdltCheck(cmdlet cmdlet_obj)
{
	auto cmdlet_it = pool_cmdlets.find(cmdlet_obj.first);
	if (cmdlet_it == pool_cmdlets.cend())
	{
		std::string mes = std::format("\"{}\" commandlet is unknown.", cmdlet_obj.first);
		throw CommandError(mes);
	}
	std::string error_mes = "";

	auto income_params = cmdlet_obj.second;

	cmdlet CmdletForm; 
	if(cmdlet_it->second.find(base_params_ident) != cmdlet_it->second.cend()) CmdletForm = getCmdletForm(cmdlet_it->first, cmdlet_it->second);
	else CmdletForm = cmdlet(cmdlet_it->first, cmdlet_it->second);

	auto& form_params = CmdletForm.second;

	for(auto& form_param : form_params)
	{	
		if (form_param.first.empty()) continue;
		auto it = income_params.find(form_param.first);
		if(it == income_params.cend())
		{
			if (form_param.second.empty()) error_mes += std::format("\"{}\" parameter for \"{}\" commandlet is required. But isn't specified! \n", form_param.first, cmdlet_obj.first);  
			continue;
		}
		form_param.second = it->second;
		income_params.erase(it);
	}

	if(!income_params.empty())
	{
		for(auto excess_param : income_params)
		{
			error_mes += std::format("\"{}\" commandlet doesn't have \"{}\" parameter.\n", cmdlet_obj.first, excess_param.first);
		}		
	}

	if (!error_mes.empty()) throw CommandError(error_mes);

	return CmdletForm;		
}

cmdlet ManagerCmdlet::getCmdletForm(const std::string& cmdlet_name, const params& par) const
{
	
	auto cmdlet_form = cmdlet(cmdlet_name, par);
	auto base_params = pool_cmdlets.at(base_params_ident);
	for (auto base_param : base_params)
	{
		cmdlet_form.second.insert(base_param);
	}
	cmdlet_form.second.erase(base_params_ident);
	return cmdlet_form;
}


//params ManagerCmdlet::cmdltCheck(params form_params, )


