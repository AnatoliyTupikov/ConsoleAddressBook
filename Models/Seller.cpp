#include "Seller.h"

Seller::Builder::Builder(std::string name, std::string last_name) : Worker::Builder(name, last_name)
{
	setPosition("Seller");

}
Seller::Builder::Builder(const nlohmann::json& j, std::shared_ptr<Office> off) : Worker::Builder(j, off)
{
	try
	{
		sales_region = j.at("sales_region");
		product_specialty = j.at("product_specialty");
	}
	catch (nlohmann::json::out_of_range ex)
	{
		std::string mess = fromJsonError;
		mess += "\n";
		mess += ex.what();
		throw DeserializingError(mess);
	}
}

Seller::Builder& Seller::Builder::reset(std::string name, std::string last_name)
{
	Worker::Builder::reset(name, last_name);
	sales_region = "Unknown";
	product_specialty = "Unknown";
	return *this;
}
Seller::Builder& Seller::Builder::setSalesRegion(std::string region)
{
	sales_region = region;
	return *this;
}
Seller::Builder& Seller::Builder::setProductSpecialty(std::string specialty)
{
	product_specialty = specialty;
	return *this;
}
std::shared_ptr<Seller> Seller::Builder::build()
{

	Seller* temp_ptr = new Seller(*this);
	auto res = std::shared_ptr<Seller>(temp_ptr);
	return res;
}

Seller::Builder& Seller::Builder::setPhone(std::string Phone, std::string Type)
{
	Worker::Builder::setPhone(Phone, Type);
	return *this;
}

Seller::Builder& Seller::Builder::setOffice(std::shared_ptr<Office> off)
{
	Worker::Builder::setOffice(off);
	return *this;
}