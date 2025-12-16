#pragma once
#include"Book.h"
#include <iostream>
#include <iomanip>


template <class T>
using WorkerPtr = std::shared_ptr<T>;

template <class T>
using WorkerList = std::vector<WorkerPtr<T>>;

using StringList = std::vector<std::string>;

class ConsoleInerface
{
public:
	ConsoleInerface();
	~ConsoleInerface();
	static void showCursor(); 

	

	template <class T>
	void showTable(
		WorkerList<T> list,
		StringList(*getHeaders)(WorkerPtr<T>),
		StringList(*getMainInfo)(WorkerPtr<T>));

private:
	static inline std::string cursor = ">";

};

ConsoleInerface::ConsoleInerface()
{
}

ConsoleInerface::~ConsoleInerface()
{
}

void ConsoleInerface::showCursor()
{
	std::cout << cursor;
}


template <class T>
void ConsoleInerface::showTable(WorkerList<T> list,
	StringList(*getHeaders)(WorkerPtr<T>),
	StringList(*getMainInfo)(WorkerPtr<T>))
	{	
	if (list.size() == 0)
	{
		std::cout << "There are no these people. Nothing to show!" << std::endl;
		return;
	}
	auto headers = getHeaders(list[0]);
	std::vector<std::vector<std::string>> res;
	res.push_back(headers);
	std::vector<size_t> max_sizes;
	for(auto el : headers)
	{
		max_sizes.push_back(el.length());
	}
	

	

	std::for_each(list.cbegin(), list.cend(),
		[&res, &max_sizes, &getMainInfo](const auto el)
		{
			auto el_to_vec_str = getMainInfo(el);
			for (int i = 0; i < el_to_vec_str.size(); i++)
			{
				max_sizes[i] = std::max(max_sizes[i], el_to_vec_str[i].length());
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

		if(j == 0) 
		{				
			for (size_t x = 0; x < sum; x++) std::cout << "=";
			std::cout << std::endl;
		}
		
		
	}
	


}

