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
    static inline unsigned long id_sequence = 0;

    //Builder clas===================
    class Builder
    {
        std::string name;
        std::string last_name;
        std::weak_ptr<Office> office;
		std::string phone_number = "-";
		std::string phone_type = "Unknown";
        std::string position = "Unknown";
        unsigned long id = 0;

    protected:
        virtual Builder& reset(std::string name, std::string last_name);
        Builder& setPosition(std::string pos);
        virtual Builder& setPhone(std::string Phone, std::string Type = "Unknown");
        virtual Builder& setOffice(std::shared_ptr<Office> off);
        const std::string fromJsonError = "Wrong parsed Data from the file, the parameter is missing";
        Builder(std::string name, std::string last_name);
        Builder(const nlohmann::json& j, std::shared_ptr<Office> off = nullptr);
        ~Builder() {};
        
    public:
        friend class Worker;
          
    };
    //Builder clas end===================

    explicit Worker(const Builder& b);    	

public:
	~Worker() {};
	static unsigned long getIdSequence() { return id_sequence; }
	static void setIdSequence(unsigned long new_sequence) { id_sequence = new_sequence;}
	std::string getName() const { return name; }
	std::string getLastName() const { return last_name; }
	unsigned long getId() const { return id; }

    std::vector<std::string> getShortInfo() const;
    static std::vector<std::string> getColums();
	virtual std::vector<std::string> getFullInfo() const = 0;
    virtual void toJSON(nlohmann::json& j) const;
};

void to_json(nlohmann::json& j, const Worker& w);



