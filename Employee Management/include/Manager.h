#pragma once
#include "Employee.h"

class Manager : public Employee {
public:

    Manager() = default;

    Manager(int id, std::string_view firstname, std::string_view lastname, std::string_view dob,
        std::string_view mobile, std::string_view email, std::string_view address,
        Gender gender, std::string_view doj, float salary, int w_location_id,
        int manager_id, int department_id, int management_experience,
        std::string_view project_title)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, salary,
             manager_id, department_id),
        management_experience(management_experience), project_title(project_title) {}

    int getManagementExperience() const { return management_experience; }
    std::string getProjectTitle() const { return project_title; }


    void setManagementExperience(int management_experience) {
        this->management_experience = management_experience;
    }
    void setProjectTitle(std::string_view project_title) {
        this->project_title = project_title;
    }

    const char* getClassName() const override {
        return "Manager";
    }

    void getUserInputForUpdate() {

        Employee::getUserInputForUpdate();

        auto me{ input("Enter Management Experience: ",emailRegex) };
        if (!(me == "#")) setManagementExperience(stoi(me));

        auto pt{ input("Enter Project Title: ") };
        if (!(pt == "#")) setProjectTitle(pt);

    }

    void getUserInput() {
        Employee::getUserInput();
        setManagementExperience(stoi(input("Enter Management Experience years: ")));
        setProjectTitle(input("Enter Project Title: "));
    }

    void display() {
        Employee::display();

        std::cout << "| Management Exp.  | " << std::setw(38) << std::left << management_experience << " |" << std::endl;
        std::cout << "| Project Title    | " << std::setw(38) << std::left << project_title << " |" << std::endl;
        std::cout << "+------------------+----------------------------------------+" << std::endl;
    }

    bool save() {
        DB dbI;
        dbI.open("Rohit.db");

        Employee::save();

        std::string insertQuery = "INSERT INTO Manager VALUES (" + std::to_string(Employee::getId()) + "," + std::to_string(management_experience) + ", '" + project_title + "');";

        if (!dbI.executeQuery(insertQuery.c_str(), "")) { return false; }
        return true;
    }

    bool deleteThis() {
        DB dbI;
        dbI.open("Rohit.db");

        Employee::deleteThis();

        std::string deleteQuery = "DELETE FROM Manager WHERE id = ";
        deleteQuery += std::to_string(getId());

        if (!dbI.executeQuery(deleteQuery.c_str(), "")) { return false; }

        return true;
    }

    bool update() {
        DB dbI;
        dbI.open("Rohit.db");

        Employee::update();

        std::string updateQuery = "UPDATE Engineer SET ";
        updateQuery +=
            "management_experience=" + std::to_string(management_experience) +
            ", project_title='" + project_title +
            " WHERE id = " + std::to_string(getId()) + ";";


        if (!dbI.executeQuery(updateQuery.c_str(), "")) return false;

        return true;
    }

    static Manager getManagerByID(int id) {
        DB dbI;
        dbI.open("Rohit.db");

        Manager m;

        std::string selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id WHERE Employee.id = " + std::to_string(id) + ";";

        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            Manager* emp = static_cast<Manager*>(data);

            emp->setId(std::stoi(argv[0]));
            emp->setFirstname(argv[1]);
            emp->setLastname(argv[2]);
            emp->setDob(argv[3]);
            emp->setMobile(argv[4]);
            emp->setEmail(argv[5]);
            emp->setAddress(argv[6]);
            emp->setGender(stringToGender(argv[7]));
            emp->setDoj(argv[8]);
            emp->setManagerId(std::stoi(argv[9]));
            emp->setDepartmentId(std::stoi(argv[10]));
            emp->setManagementExperience(std::stoi(argv[12]));
            emp->setProjectTitle(argv[13]);

            return 0;
            };

        dbI.executeSelectQuery(selectQuery.c_str(), callback, &m, "");

        return m;
    }

    static std::vector<Manager> getMultipleManagers(const std::string& queryField = "", const std::string& queryValue = "") {
        DB dbI;
        dbI.open("Rohit.db");

        std::vector<Manager> vecOfEmp;

        std::string selectQuery;


        if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
            selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = " + queryValue + "; ";

        }
        else if (queryField == "" && queryValue == "") {
            selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id JOIN Department ON Employee.department_id = Department.id ;";
        }
        else {
            selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = '" + queryValue + "';";
        }


        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            std::vector<Manager>* vecOfEmp = static_cast<std::vector<Manager>*>(data);

            Manager emp;

            emp.setId(std::stoi(argv[0]));
            emp.setFirstname(argv[1]);
            emp.setLastname(argv[2]);
            emp.setDob(argv[3]);
            emp.setMobile(argv[4]);
            emp.setEmail(argv[5]);
            emp.setAddress(argv[6]);
            emp.setGender(stringToGender(argv[7]));
            emp.setDoj(argv[8]);
            emp.setManagerId(std::stoi(argv[9]));
            emp.setDepartmentId(std::stoi(argv[10]));
            emp.setManagementExperience(std::stoi(argv[12]));
            emp.setProjectTitle(argv[13]);

            vecOfEmp->push_back(std::move(emp));
            return 0;
            };

        dbI.executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "");

        return vecOfEmp;
    }

private:

    int management_experience;
    std::string project_title;
};
