#pragma once
#include <iostream>
#include <string>
#include "Regex.h"
#include "Helper.h"
#include "DB.h"
#include "Employee.h"



class Department {
public:

    Department() = default;

    Department(int id, const std::string& name, int manager_id, const std::string& description)
        : id(id), name(name), manager_id(manager_id), description(description) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getManagerId() const { return manager_id; }
    std::string getDescription() const { return description; }

    void setId(int id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }
    void setManagerId(int manager_id) { this->manager_id = manager_id; }
    void setDescription(const std::string& description) { this->description = description; }


    void display() const {

        auto e = Employee::getEmployeeById(manager_id);
        std::string managerName = e.value().getFirstname() + " " + e.value().getLastname() + " - ID:(" + std::to_string(manager_id) + ")";

        std::cout << "+------------------+----------------------------------------+" << std::endl;
        std::cout << "|\033[32m ID\033[0m               | " << std::setw(38) << std::left << id << " |" << std::endl;
        std::cout << "| Department Name  | " << std::setw(38) << std::left << name        << " |" << std::endl;
        std::cout << "| Manager Name     | " << std::setw(38) << std::left << managerName << " |" << std::endl;
        std::cout << "| Description      | " << std::setw(38) << std::left << description << " |" << std::endl;
        std::cout << "+------------------+----------------------------------------+" << std::endl;
    }

    void getUserInput() {
        setId(stoi(input("Enter Department ID: ")));
        setName(input("Enter Department Name: "));
        setManagerId(stoi(input("Enter Department Manager Id: ")));
        setDescription(input("Enter Description: "));
    }

    void getUserInputForUpdate() {
        auto id{ input("Enter Department ID: ",idRegex) };
        if (!(id != "#")) { setId(stoi(id)); }

        auto name{ input("Enter Department Name: ") };
        if (!(name != "#")) { setName(name); }

        auto mid{ input("Enter Manager ID: ", idRegex) };
        if (!(mid != "#")) { setManagerId(manager_id); }

        auto desc{ input("Enter brief Description: ") };
        if (!(desc != "#")) { setDescription(desc); }
    }


    bool save() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string  insertQuery = "INSERT INTO Department "
            "(id, name, manager_id, description) VALUES (";

        insertQuery += std::to_string(id) +
            ",'" + name +
            "'," + std::to_string(manager_id) +
            ",'" + description + "');";

        if (!dbI.executeQuery(insertQuery.c_str(), "Inserted Successfully\n")) { return false; }

        return true;
    }


    static Department getDepartment(int id) {
        DB dbI;
        dbI.open("Rohit.db");

        Department dpt;

        std::string selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(id) + ";";

        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            Department* dpt = static_cast<Department*>(data);

            dpt->setId(std::stoi(argv[0]));
            dpt->setName(argv[1]);
            dpt->setManagerId(std::stoi(argv[2]));
            dpt->setDescription(argv[3]);
            return 0;
            };

        dbI.executeSelectQuery(selectQuery.c_str(),callback , &dpt);

        return dpt;
    }


    static std::vector<Department> getMultipleDepartment(const std::string& queryField = "", const std::string& queryValue = "") {
        DB dbI;
        dbI.open("Rohit.db");

        std::vector<Department> vecOfDep;

        std::string selectQuery;

        if (queryField == "id" || queryField == "manager_id" ) {
            selectQuery = "SELECT Department.* FROM Employee JOIN Department ON Employee.id = Department.manager_id WHERE " + queryField + " = " + queryValue + "; ";

        }
        else if (queryField == "" && queryValue == "") {
            selectQuery = "SELECT Department.* FROM Employee JOIN Department ON Employee.id = Department.manager_id ;";
        }
        else {
            selectQuery = "SELECT Department.* FROM Employee JOIN Department ON Employee.id = Department.manager_id WHERE " + queryField + " = '" + queryValue + "';";
        }


        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            std::vector<Department>* vecOfDep = static_cast<std::vector<Department>*>(data);

            Department dpt;

            dpt.setId(std::stoi(argv[0]));
            dpt.setName(argv[1]);
            dpt.setManagerId(std::stoi(argv[2]));
            dpt.setDescription(argv[3]);

            vecOfDep->push_back(std::move(dpt));

            return 0;
        };

        dbI.executeSelectQuery(selectQuery.c_str(), callback, &vecOfDep, "");

        return vecOfDep;
          
    }


    bool deleteThis() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string deleteQuery = "DELETE FROM Department WHERE id = ";
        deleteQuery += std::to_string(id);

        if (!dbI.executeQuery(deleteQuery.c_str(), "Deleted Successfully\n")) { return false; }

        return true;
    }

    bool update() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string updateQuery = "UPDATE Department SET ";
        updateQuery +=
            "name='" + name +
            "', manager_id=" + std::to_string(manager_id) +
            ", description='" + description +
            "' WHERE id = " + std::to_string(id) + ";";


        if (!dbI.executeQuery(updateQuery.c_str(), "Department Updated Successfully\n")) return false;

        return true;
    }



private:

    int id;
    std::string name;
    int manager_id;
    std::string description;

};
