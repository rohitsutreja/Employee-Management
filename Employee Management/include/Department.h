#pragma once
#include <iostream>
#include <string>
#include "Regex.h"
#include "Util.h"
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
        auto dbI = DB::getDB();

        std::string managerName = "";
        std::string selectQuery = "SELECT firstname, lastname FROM EMPLOYEE WHERE id = " + std::to_string(manager_id) + ";";
        dbI->executeSelectQuery(selectQuery.c_str(), [](void* data, int argc, char** argv , char** aZcolname) {
            auto m = static_cast<std::string*>(data);

            *m += argv[0];
            *m += " ";
            *m += argv[1];

            return 0;
            }, & managerName, "Employee name selected to display department");

        managerName += " ( ID - ";
        managerName += std::to_string(manager_id) + ")";

        if (manager_id == -1) {
            managerName = "-";
        }

        std::cout << "+------------------+----------------------------------------+" << std::endl;
        std::cout << "|\033[32m ID\033[0m               | " << std::setw(38) << std::left << id << " |" << std::endl;
        std::cout << "| Department Name  | " << std::setw(38) << std::left << name        << " |" << std::endl;
        std::cout << "| Manager Name     | " << std::setw(38) << std::left << managerName  << " |" << std::endl;
        std::cout << "| Description      | " << std::setw(38) << std::left << description << " |" << std::endl;
        std::cout << "+------------------+----------------------------------------+" << std::endl;
    }

    void getUserInput() {
        setId(stoi(input("Enter Department ID: ", idRegex)));
        setName(input("Enter Department Name: ", nonEmptyRegex));
        auto mId = input("Enter Department Manager Id ('#' to skip): ", idRegex, true);
        if (mId == "#") {
           setManagerId(-1);
        }
        else {
            setManagerId(stoi(mId));
        }
        
        setDescription(input("Enter Description: ", nonEmptyRegex));
    }

    void getUserInputForUpdate() {
        std::cout << "Update Department with id: " << id << '\n\n';
        auto name{ input("Enter Department Name: ", nonEmptyRegex , true) };
        if ((name != "#")) { setName(name); }

        auto mid{ input("Enter Manager ID: ", idRegex , true) };
        if ((mid != "#")) { setManagerId(manager_id); }

        auto desc{ input("Enter brief Description: ", nonEmptyRegex , true) };
        if ((desc != "#")) { setDescription(desc); }
    }


    bool save() {
        auto dbI = DB::getDB();

        std::string  insertQuery = "INSERT INTO Department "
            "(id, name, manager_id, description) VALUES (";

        insertQuery += std::to_string(id) +
            ",'" + name +
            "'," + std::to_string(manager_id) +
            ",'" + description + "');";

        if (!dbI->executeQuery(insertQuery.c_str(), "A Departement Inserted with ID: " + std::to_string(id) + "\n")) { return false; }

        return true;
    }


    static std::optional<Department> getDepartment(int id) {
        auto dbI = DB::getDB();


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

        dbI->executeSelectQuery(selectQuery.c_str(),callback , &dpt, "Department selected with ID " + std::to_string(id));

        if (dpt.getId() == 0) {
            return std::nullopt;
        }
        return dpt;
    }


    static std::vector<Department> getMultipleDepartment(const std::string& queryField = "", const std::string& queryValue = "") {
        auto dbI = DB::getDB();


        std::vector<Department> vecOfDep;

        std::string selectQuery;

        if (queryField == "id" || queryField == "manager_id" ) {
            selectQuery = "SELECT Department.* FROM Department LEFT  JOIN Employee ON Employee.id = Department.manager_id WHERE " + queryField + " = " + queryValue + "; ";

        }
        else if (queryField == "" && queryValue == "") {
            selectQuery = "SELECT Department.* FROM Department LEFT JOIN Employee ON Employee.id = Department.manager_id ;";
        }
        else {
            selectQuery = "SELECT Department.* FROM Department LEFT JOIN Employee ON Employee.id = Department.manager_id WHERE " + queryField + " = '" + queryValue + "';";
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

        dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfDep, "Multiple Department selected.");

        return vecOfDep;
          
    }


    bool deleteThis() {
        auto dbI = DB::getDB();


        std::string deleteQuery = "DELETE FROM Department WHERE id = ";
        deleteQuery += std::to_string(id);

        if (!dbI->executeQuery(deleteQuery.c_str(), "Department Deleted with ID: " + std::to_string(id) + ".")) { return false; }

        return true;
    }

    bool update() {
        auto dbI = DB::getDB();


        std::string updateQuery = "UPDATE Department SET ";
        updateQuery +=
            "name='" + name +
            "', manager_id=" + std::to_string(manager_id) +
            ", description='" + description +
            "' WHERE id = " + std::to_string(id) + ";";


        if (!dbI->executeQuery(updateQuery.c_str(), "Department Updated with ID: " + std::to_string(id) + ".")) return false;

        return true;
    }



private:

    int id{};
    std::string name;
    int manager_id{};
    std::string description;

};
