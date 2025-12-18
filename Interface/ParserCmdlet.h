#pragma once
#include <string>
#include <map>
#include<utility>
#include<sstream>
#include <algorithm>
#include <format>
#include"../Exceps/CommandError.h"

class ParserCmdlet
{
	ParserCmdlet();
	~ParserCmdlet();
public:
	static std::string toLowerOneWord(std::string source);
	static std::string toLower(const std::string& s);
	static unsigned long idFromString(std::string str_id, std::string err_mes = "");
	static std::pair<std::string, std::map<std::string, std::string>> Parse(const std::string str);
	
};

