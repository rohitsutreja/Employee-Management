#pragma once
#include <iostream>
#include <string>
class Department {
public:

    Department(int id, const std::string& name, int manager_id, const std::string& description)
        : id(id), name(name), manager_id(manager_id), description(description) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getManagerId() const { return manager_id; }
    std::string getDescription() const { return description; }

private:

    int id;
    std::string name;
    int manager_id;
    std::string description;
};
