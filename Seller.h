#pragma once
#include "Worker.h"

class Seller : public Worker
{
	class Builder;
	std::string sales_region = "Unknown";
	std::string product_specialty = "Unknown";
	Seller(const Seller::Builder& b) : Worker(b) 
	{
		sales_region = b.sales_region;
		product_specialty = b.product_specialty;
	}

public:
	class Builder : public Worker::Builder
	{
		//std::shared_ptr<Seller> seller;
		std::string sales_region = "Unknown";
		std::string product_specialty = "Unknown";

	public:
		Builder(std::string name, std::string last_name) : Worker::Builder(name, last_name)
		{
			setPosition("Seller");			
			//Seller* temp_ptr = new Seller(*this);
			//seller = std::shared_ptr<Seller>(temp_ptr);
		}
		Builder(const nlohmann::json& j, std::shared_ptr<Office> off = nullptr) : Worker::Builder(j, off)
		{
			sales_region = j["sales_region"];
			product_specialty = j["product_specialty"];
		}
		~Builder() {};
		Builder& reset (std::string name, std::string last_name) override
		{
			Worker::Builder::reset(name, last_name);
			sales_region = "Unknown";
			product_specialty = "Unknown";
			//Seller* temp_ptr = new Seller(*this);
			//seller = std::shared_ptr<Seller>(temp_ptr);
			return *this;
		}
		Builder& setSalesRegion(std::string region)
		{
			sales_region = region;
			return *this;
		}
		Builder& setProductSpecialty(std::string specialty)
		{
			product_specialty = specialty;
			return *this;
		}
		std::shared_ptr<Seller> build()
		{
			
			Seller* temp_ptr = new Seller(*this);
			auto res = std::shared_ptr<Seller>(temp_ptr);
			return res;
		}

		Builder& setPhone(std::string Phone, std::string Type = "Unknown") override
		{
			Worker::Builder::setPhone( Phone,  Type);
			return *this;
		}

		Builder& setOffice(std::shared_ptr<Office> off) override
		{
			Worker::Builder::setOffice(off);
			return *this;
		}

		

		friend class Seller;

	};
	void toJSON(nlohmann::json& j) const override
	{
		Worker::toJSON(j);
		j["sales_region"] = sales_region;
		j["product_specialty"] = product_specialty;
	}

	friend class Builder;

	std::vector<std::string> getFullInfo() const override
	{
		
		std::vector<std::string> info;
		info.push_back(name);
		info.push_back(last_name);
		info.push_back(phone.getPhone());
		info.push_back(phone.getType());
		info.push_back(position);		
		info.push_back(sales_region);
		info.push_back(product_specialty);
		info.push_back(office.lock() ? office.lock()->getName() : "No Office Assigned");
		info.push_back(office.lock() ? office.lock()->getAddress() : "-");
		info.push_back(std::to_string(id));
		return info;
		
	}

	std::vector<std::string> getColums() const override
	{
		return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " Sales Region ", " Product Specialty ", " Office Name ", " Office Address ", " ID " };
	}


};
