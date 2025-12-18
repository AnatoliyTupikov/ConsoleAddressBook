#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include "ParserCmdlet.h"




class ConsoleInterface
{
	ConsoleInterface();
	~ConsoleInterface();
	
public:
	static std::string requestString(std::string dialog);

	static std::pair<std::string, std::map<std::string, std::string>> requestCommand();

	static void showError(std::string mes);

	static void showMessage(std::string mes);

	
	template <class T>
	using WorkerPtr = std::shared_ptr<T>;
	template <class T>
	using WorkerList = std::vector<WorkerPtr<T>>;
	using StringList = std::vector<std::string>;

	template <class T>
	static void showList(
		WorkerList<T> list,
		StringList headers,
		StringList(*getMainInfo)(WorkerPtr<T>));

private:
	static inline std::string cursor = ">";

};

template <class T>
void ConsoleInterface::showList(WorkerList<T> list, StringList headers,
	StringList(*getFieldsValue)(WorkerPtr<T>))
{
	if (list.size() == 0)
	{
		std::cout << "There are no objects. Nothing to show!" << std::endl;
		return;
	}

	std::vector<std::vector<std::string>> res;
	res.push_back(headers);
	std::vector<size_t> max_sizes;
	for (auto el : headers)
	{
		max_sizes.push_back(el.length());
	}

	std::for_each(list.cbegin(), list.cend(),
		[&res, &max_sizes, &getFieldsValue](const auto el)
		{
			auto el_to_vec_str = getFieldsValue(el);
			for (int i = 0; i < el_to_vec_str.size(); i++)
			{
				max_sizes[i] = (std::max)(max_sizes[i], el_to_vec_str[i].length());
			}
			res.push_back(el_to_vec_str);
		});

	for (int j = 0; j <= res.size(); j++)

	{
		size_t sum = max_sizes.size();
		for (auto el : max_sizes) sum += el;
		if (j == 0)
		{

			for (size_t x = 0; x < sum; x++) std::cout << "=";
			std::cout << std::endl;
		}
		else if (j == res.size())
		{
			for (size_t x = 0; x < sum; x++) std::cout << "‾";
			std::cout << std::endl;
			break;

		}

		auto row = res[j];

		for (int i = 0; i < row.size(); i++)
		{
			std::cout << std::left << std::setw(max_sizes[i]) << row[i] << "|";

		}
		std::cout << std::endl;

		if (j == 0)
		{
			for (size_t x = 0; x < sum; x++) std::cout << "=";
			std::cout << std::endl;
		}
	}
}



