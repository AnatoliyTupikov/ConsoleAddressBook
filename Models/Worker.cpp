#pragma once
#include "Worker.h"

Worker::Builder::Builder(std::string name, std::string last_name) : name(name), last_name(last_name) {}

Worker::Builder::Builder(const nlohmann::json& j, std::shared_ptr<Office> off)
{
    try
    {
        id = 0;
        if (j.at("id").is_number_unsigned()) { id = j.at("id").get<unsigned long>(); }
        name = j.at("name");
        last_name = j.at("last_name");
        phone_number = j.at("phone");
        phone_type = j.at("phone_type");
        position = j.at("position");
        office = std::weak_ptr(off);
    }
    catch (nlohmann::json::out_of_range ex)
    {
        std::string mess = fromJsonError;
        mess += "\n";
        mess += ex.what();
        throw DeserializingError(mess);
    }
}

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

Worker::Worker(const Builder& b)
{
    if (b.id <= 0) id = ++id_sequence;
    else id = b.id;
    name = b.name;
    last_name = b.last_name;
    office = b.office;
    phone.setPhone(b.phone_number);
    phone.setType(b.phone_type);
    position = b.position;
}

std::vector<std::string> Worker::getShortInfo() const
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

void Worker::toJSON(nlohmann::json& j) const
{
    j = nlohmann::json
    {

        {"name", name},
        {"last_name", last_name},
        {"office", office.lock() ? office.lock()->getId() : 0},
        {"phone", phone.getPhone()},
        {"phone_type", phone.getType()},
        {"position", position},
        {"id", id }
    };

}

std::vector<std::string> Worker::getColums() {
    return { " Name ", " Last Name ", " Phone ", " Phone Type ", " Position ", " ID " };
}

void to_json(nlohmann::json& j, const Worker& w)
{
    w.toJSON(j);
}