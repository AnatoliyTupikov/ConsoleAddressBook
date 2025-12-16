#pragma once
#include <string>
#include "Telephone.h"
#include "Office.h"
#include <memory>
#include <vector>
#include <nlohmann/json.hpp>

class Worker
{
    
        
protected:
	std::string name;
	std::string last_name;
    std::weak_ptr<Office> office;
	Telephone phone;
	unsigned long id;
	std::string position = "Unknown";
	

    class Builder
    {
        std::string name;
        std::string last_name;
        std::weak_ptr<Office> office;
		std::string phone_number = "-";
		std::string phone_type = "Unknown";
        std::string position = "Unknown";
        
        
    public:
        friend class Worker;
		Builder(std::string name, std::string last_name) : name(name), last_name(last_name) {}
        Builder(const nlohmann::json& j, std::shared_ptr<Office> off = nullptr)
        {
            name = j["name"];
            last_name = j["last_name"];
            phone_number = (j["phone"]);
            phone_type = (j["phone_type"]);
            position = j["position"];
            office = std::weak_ptr(off);
        }
        ~Builder() {};		       
    protected:        
        virtual Builder& reset(std::string name, std::string last_name);
        Builder& setPosition(std::string pos);
        virtual Builder& setPhone(std::string Phone, std::string Type = "Unknown");
        virtual Builder& setOffice(std::shared_ptr<Office> off);
    };

    explicit Worker(const Builder& b)
    {
        id = ++id_sequence;
        name = b.name;
        last_name = b.last_name;
        office = b.office;
        phone.setPhone(b.phone_number);
        phone.setType(b.phone_type);
        position = b.position;
    }

private:
    static inline unsigned long id_sequence = 0;
    	

public:
	~Worker() {};
	static unsigned long getIdSequence() { return id_sequence; }
	static void setIdSequence(unsigned long new_sequence) { id_sequence = new_sequence;}
    friend class Builder;

	std::string getName() const { return name; }
	std::string getLastName() const { return last_name; }
	unsigned long getId() const { return id; }

    std::vector<std::string> getShortInfo() const
    {
        std::vector<std::string> info;
        info.push_back(name);
        info.push_back(last_name);
        info.push_back(phone.getPhone());
		info.push_back(phone.getType());
		info.push_back(position);
        info.push_back(std::to_string(id));

        return info;
    }

    virtual void toJSON(nlohmann::json& j) const
    {
        j = nlohmann::json
        {
            {"name", name},
            {"last_name", last_name},
            {"office", office.lock() ? office.lock()->getId() : 0},
            {"phone", phone.getPhone()},
            {"phone_type", phone.getType()},
            {"position", position}
        };

    }




    virtual std::vector<std::string> getShortColums() {
        return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " ID " };
    }
    virtual std::vector<std::string> getColums() const = 0;
    


	virtual std::vector<std::string> getFullInfo() const = 0;


};



Worker::Builder& Worker::Builder::setPhone(std::string phone, std::string type)
{
	phone_number = phone;
	phone_type = type;
    return *this;
}
Worker::Builder& Worker::Builder::setOffice(std::shared_ptr<Office> off)
{
	office = std::weak_ptr<Office>(off);
    return *this;
}

Worker::Builder& Worker::Builder::reset(std::string worker_name, std::string worker_last_name)
{
    name = worker_name;
    last_name = worker_last_name;
    office.reset();
    phone_number = "-";
    phone_type = "Unknown";
    position = "Unknown";
    return *this;
}
Worker::Builder& Worker::Builder::setPosition(std::string pos)
{
    position = pos;
    return *this;
}

void to_json(nlohmann::json& j, const Worker& w) 
{
    w.toJSON(j);
}


