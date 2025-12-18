#pragma once
#include "Worker.h"

class Seller : public Worker
{
	
	std::string sales_region = "Unknown";
	std::string product_specialty = "Unknown";
	class Builder;
	Seller(const Seller::Builder& b) : Worker(b) 
	{
		sales_region = b.sales_region;
		product_specialty = b.product_specialty;
	}

public:
	const static inline std::string Path = "DataStore/sellers.txt";

	class Builder : public Worker::Builder
	{		
		std::string sales_region = "Unknown";
		std::string product_specialty = "Unknown";	

	public:
		Builder(std::string name, std::string last_name);
		Builder(const nlohmann::json& j, std::shared_ptr<Office> off = nullptr);
		~Builder() {};
		Builder& reset(std::string name, std::string last_name) override;
		Builder& setSalesRegion(std::string region);
		Builder& setProductSpecialty(std::string specialty);
		std::shared_ptr<Seller> build();
		Builder& setPhone(std::string Phone, std::string Type = "Unknown") override;
		Builder& setOffice(std::shared_ptr<Office> off) override;
		friend class Seller;
	};

	void toJSON(nlohmann::json& j) const override
	{
		Worker::toJSON(j);
		j["sales_region"] = sales_region;
		j["product_specialty"] = product_specialty;
	}

	//friend class Builder;

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

	static std::vector<std::string> getColums() 
	{
		return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " Sales Region ", " Product Specialty ", " Office Name ", " Office Address ", " ID " };
	}

};
