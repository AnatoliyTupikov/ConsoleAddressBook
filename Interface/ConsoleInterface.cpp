#pragma once
#include "ConsoleInterface.h"

ConsoleInterface::ConsoleInterface()
{
}

ConsoleInterface::~ConsoleInterface()
{

}

std::string ConsoleInterface::requestString(std::string dialog = "")
{
	std::cout << dialog << cursor;
	std::string str;
	std::getline(std::cin, str);
	return str;
}

std::pair<std::string, std::map<std::string, std::string>> ConsoleInterface::requestCommand()
{
	std::string str = requestString();
	if (str.empty()) return { "", {} };
	return ParserCmdlet::Parse(str);
}

void ConsoleInterface::showError(std::string mes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD saved_attributes = consoleInfo.wAttributes;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	std::cout << mes << std::endl;
	// Сброс к стандартному цвету
	SetConsoleTextAttribute(hConsole, saved_attributes);
}

void ConsoleInterface::showMessage(std::string mes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD saved_attributes = consoleInfo.wAttributes;
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
	std::cout << mes << std::endl;
	// Сброс к стандартному цвету
	SetConsoleTextAttribute(hConsole, saved_attributes);
}
