#include "Book.h"

Book* Book::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Book();
	}
	return instance;
}


std::vector<std::shared_ptr<Office>> Book::getOffices() const
{
	return getAllSortedObjects(offices);
}

std::shared_ptr<Office> Book::getOffice(unsigned long id)
{
	std::shared_ptr<Office> res = nullptr;
	auto it = offices.find(id);
	if (it != offices.cend()) res = it->second;
	return res;
}

std::vector<std::shared_ptr<Worker>> Book::getWorkers() const
{
	return getAllSortedObjects(workers);
}

std::shared_ptr<Worker> Book::getWorker(unsigned long id) const
{
	std::shared_ptr<Worker> res = nullptr;
	auto it = workers.find(id);
	if (it != workers.cend()) res = it->second;
	return res;
}

bool Book::addWorker(const std::shared_ptr<Worker> w)
{
	if (workers.find(w->getId()) != workers.end()) return false;
	workers[w->getId()] = w;
	return true;
}

bool Book::removeWorker(const unsigned long& id)
{
	return workers.erase(id) > 0;
}

bool Book::addOffice(const std::shared_ptr<Office> o)
{
	if (offices.find(o->getId()) != offices.end()) return false;
	offices[o->getId()] = o;
	return true;
}

bool Book::removeOffice(const unsigned long& id)
{

	return offices.erase(id) > 0;
}

void Book::syncId()
{
	if (!workers.empty())
	{
		auto maxIt = std::max_element(
			workers.begin(), workers.end(),
			[](const auto& a, const auto& b) {
				return a.first < b.first;
			}
		);
		Worker::setIdSequence(maxIt->first);
	}


	if (!offices.empty())
	{
		auto maxIt = std::max_element(
			offices.begin(), offices.end(),
			[](const auto& a, const auto& b) {
				return a.first < b.first;
			}
		);
		Office::setIdSequence(maxIt->first);
	}
}