#ifndef DEPARTMENT_H
#define DEPARTMENT_H


#include <iostream>
#include <string>
#include "../Util.h"
#include "../DB.h"
#include "Employee.h"

class Department {
public:
    Department() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getManagerId() const { return manager_id; }
    std::string getDescription() const { return description; }

    void setId(int id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }
    void setManagerId(int manager_id) { this->manager_id = manager_id; }
    void setDescription(const std::string& description) { this->description = description; }


    void display() const;

    bool getUserInput();
    bool getUserInputForUpdate();

    bool save();
    static std::optional<Department> getDepartmentById(int id);
    static std::vector<Department> getMultipleDepartment(const std::string& queryField = "", const std::string& queryValue = "");
    bool deleteThis();
    bool update();


private:
    int id{};
    std::string name;
    int manager_id{};
    std::string description;
};


#endif

