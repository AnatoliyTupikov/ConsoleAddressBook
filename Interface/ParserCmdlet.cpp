#pragma once
#include "ParserCmdlet.h"


ParserCmdlet::ParserCmdlet()
{
}

ParserCmdlet::~ParserCmdlet()
{
}

std::string ParserCmdlet::toLower(const std::string& s) {
	std::string result = s;

	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) {
			return static_cast<char>(std::tolower(c));
		});

	return result;
}

std::string ParserCmdlet::toLowerOneWord(std::string source)
{
	source = ParserCmdlet::toLower(source);
	std::stringstream ss(source);
	source = "";
	std::string temp;
	while (ss >> temp)
	{
		source += temp;
	}
	return source;
}

unsigned long ParserCmdlet::idFromString(std::string str_id, std::string err_mes)
{
	if(err_mes.empty()) err_mes = std::format("\"{}\" is wrong value for ID. It must be integer > 0.\n", str_id);	
	
	unsigned long id = 0;
	try {
		id = std::stoul(str_id);
	}
	catch (const std::invalid_argument& e) { throw CommandError(err_mes); }
	return id;
}

std::pair<std::string, std::map<std::string, std::string>> ParserCmdlet::Parse(const std::string str)
{
	if (str.empty()) throw std::invalid_argument("It's impossible to parse empty string!");
	std::pair<std::string, std::map<std::string, std::string>> res;
	std::stringstream ss(str);

	std::string cmndlt;
	ss >> cmndlt;
	res.first = toLower(cmndlt);
	std::string temp;
	std::string before_temp;
	bool isParam = true;
	while (ss >> temp)
	{
		if (isParam && temp[0] != '-')
		{
			std::string mes = std::format("Wrong parameter name format: \"{}\". Right format: -parameter_name \"<parmeter_value>\"", temp);
			throw CommandError(mes);
		}

		if (temp[0] == '-')
		{
			if (temp.size() < 2) { throw CommandError("Parameter name is not specified."); }


			if (!isParam)
			{
				std::string mes = std::format("\"{}\" parameter is specified, but not set.", before_temp);
				throw CommandError(mes);
			}

			std::string par_name = toLower(temp.substr(1));
			before_temp = par_name;

			auto it = res.second.find(par_name);
			if (it != res.second.cend())
			{
				std::string mes = std::format("\"{}\" parameter is defined multiple times, leading to an ambiguous value.", par_name);
				throw CommandError(mes);
			}

			res.second[par_name] = "";
			isParam = false;
			continue;
		}


		if (temp[0] == '"')
		{
			ss.seekg(-((long)temp.size() - 1), std::ios::cur);
			std::string par_value;
			char c;
			bool isBroken = false;
			while (ss.get(c))
			{
				if (c == '"') { isBroken = true; break; }
				par_value += c;
			}
			if (!isBroken)
			{
				std::string mes = std::format("There is no closing quotation mark or whitespase after the quotation mark for \"{}\" parameter's value", before_temp);
				throw CommandError(mes);
			}

			res.second[before_temp] = par_value;
		}
		else
		{
			res.second[before_temp] = temp;
		}
		isParam = true;
	}

	if (!isParam)
	{
		std::string mes = std::format("\"{}\" parameter is specified, but not set.", before_temp);
		throw CommandError(mes);
	}

	return res;
}