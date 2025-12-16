#pragma once
#include "Worker.h"
#include "Seller.h"
#include "Developer.h"
#include "Supporter.h"
#include <unordered_map>
#include <algorithm>
#include <concepts>
#include <iostream>

class Book
{
	static inline Book* instance = nullptr;
	std::unordered_map<unsigned long, std::shared_ptr<Worker>> workers;
	std::unordered_map<unsigned long, std::shared_ptr<Office>> offices;

	template <class T>
	std::vector<std::shared_ptr<T>> getAllSortedObjects(std::unordered_map<unsigned long, std::shared_ptr<T>> list) const
	{
		std::vector<std::shared_ptr<T>> sorted_workers;
		for (auto el : list)
		{
			sorted_workers.push_back(el.second);
		}
		std::sort(sorted_workers.begin(), sorted_workers.end(),
			[](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) {
				return a->getName() < b->getName();
			});

		return sorted_workers;
	}
	
protected:
	Book() {};

public:	
	~Book() {};
	static Book* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Book();
		}
		return instance;
	}


	std::vector<std::shared_ptr<Office>> getOffices() const
	{
		return getAllSortedObjects(offices);
	}

	std::shared_ptr<Office> getOffice(unsigned long id)
	{
		std::shared_ptr<Office> res = nullptr;
		auto it = offices.find(id);
		if (it != offices.cend()) res = it->second;
		return res;
	}

	std::vector<std::shared_ptr<Worker>> getWorkers() const
	{
		return getAllSortedObjects(workers);
	}

	template <class T>
		requires (std::is_base_of<Worker, T>::value)
	std::vector<std::shared_ptr<T>> getConcreteWorkers() const
	{
		auto sorted_workers = getWorkers();
		auto res = std::vector<std::shared_ptr<T>> ();
		std::for_each(sorted_workers.cbegin(), sorted_workers.cend(),
			[&res](const auto el)
			{
				if(auto ch = std::dynamic_pointer_cast<T>(el))
				{
					res.push_back(ch);
				}
			});
		return res;
	}



	bool addWorker(const std::shared_ptr<Worker> w)
	{
		if (workers.find(w->getId()) != workers.end()) return false;
		workers[w->getId()] = w;
		return true;
	}

	bool removeWorker(const unsigned long& id)
	{		
		return workers.erase(id) > 0;
	}

	bool addOffice(const std::shared_ptr<Office> o)
	{
		if (offices.find(o->getId()) != offices.end()) return false;
		offices[o->getId()] = o;
		return true;
	}

	bool removeOffice(const unsigned long& id)
	{
			
		return offices.erase(id) > 0;
	}


	




	
};



