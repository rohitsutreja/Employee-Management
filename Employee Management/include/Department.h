#pragma once
#include <iostream>
#include <string>
#include "Regex.h"
#include "Helper.h"
#include "DB.h"
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
        std::cout << "Department ID: " << id << std::endl;
        std::cout << "Department Name: " << name << std::endl;
        std::cout << "Department Manager Id: " << manager_id << std::endl;
        std::cout << "Description: " << description << std::endl;
    }

    void getUserInput() {
        setId(stoi(input("Enter Department ID: ")));
        setName(input("Enter Department Name: "));
        setManagerId(stoi(input("Enter Department Manager Id: ")));
        setDescription(input("Enter Description: "));
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
        dbI.executeSelectQuery(selectQuery.c_str(), selectCallback, &dpt);

        return dpt;
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

    static int selectCallback(void* data, int argc, char** argv, char** azColName) {
        Department* dpt = static_cast<Department*>(data);

        dpt->setId(std::stoi(argv[0]));
        dpt->setName(argv[1]);
        dpt->setManagerId(std::stoi(argv[2]));
        dpt->setDescription(argv[3]);
        return 0;
    }
};
