#pragma once

#include <iostream>
#include <string>
#include"DB.h"
#include "Helper.h"
#include "Regex.h"
#include<iomanip>
#include <typeinfo>
#include<optional>




enum class Gender { Male, Female, Other };

std::string genderToString(Gender g) {
    switch (g) {
    case Gender::Male:
        return "Male";
    
    case Gender::Female:
        return "Female";

    case Gender::Other:
        return "Other";
    }
    return "Male";
}


Gender stringToGender(std::string_view s) {
    if (s == "Male") {
        return Gender::Male;
    }
    else if (s == "Female") {
        return Gender::Female;
    }
    else {
        return Gender::Other;
    }
}



class Employee {

public:
    Employee() = default;

    Employee(int id, const std::string& firstname, const std::string& lastname, const std::string& dob,
        const std::string& mobile, const std::string& email, const std::string& address,
        Gender gender, const std::string& doj, int w_location_id,
        int manager_id, int department_id)
        : id(id), firstname(firstname), lastname(lastname), dob(dob), mobile(mobile), email(email),
        address(address), gender(gender), doj(doj),
        manager_id(manager_id), department_id(department_id) {}

    int getId() const { return id; }
    std::string getFirstname() const { return firstname; }
    std::string getLastname() const { return lastname; }
    std::string getDob() const { return dob; }
    std::string getMobile() const { return mobile; }
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
    Gender getGender() const { return gender; }
    std::string getDoj() const { return doj; }
    int getManagerId() const { return manager_id; }
    int getDepartmentId() const { return department_id; }


    void setId(int id) { this->id = id; }
    void setFirstname(const std::string& firstname) { this->firstname = firstname; }
    void setLastname(const std::string& lastname) { this->lastname = lastname; }
    void setDob(const std::string& dob) { this->dob = dob; }
    void setMobile(const std::string& mobile) { this->mobile = mobile; }
    void setEmail(const std::string& email) { this->email = email; }
    void setAddress(const std::string& address) { this->address = address; }
    void setGender(Gender g) { this->gender = g; }
    void setDoj(const std::string& doj) { this->doj = doj; }
    void setManagerId(int manager_id) { this->manager_id = manager_id; }
    void setDepartmentId(int department_id) { this->department_id = department_id; }

    void display() const {

        
        std::cout << "+------------------+----------------------------------------+" << std::endl;
        std::cout << "|\033[32m ID\033[0m               | " << std::setw(38) << std::left << id << " |" << std::endl;
        std::cout << "| First Name       | " << std::setw(38) << std::left << firstname << " |" << std::endl;
        std::cout << "| Last Name        | " << std::setw(38) << std::left << lastname << " |" << std::endl;
        std::cout << "| Date of Birth    | " << std::setw(38) << std::left << dob << " |" << std::endl;
        std::cout << "| Mobile           | " << std::setw(38) << std::left << mobile << " |" << std::endl;
        std::cout << "| Email            | " << std::setw(38) << std::left << email << " |" << std::endl;
        std::cout << "| Address          | " << std::setw(38) << std::left << address << " |" << std::endl;
        std::cout << "| Gender           | " << std::setw(38) << std::left << genderToString(gender) << " |" << std::endl;
        std::cout << "| Date of Joining  | " << std::setw(38) << std::left << doj << " |" << std::endl;

        auto e = Employee::getEmployeeById(manager_id);

        std::string m_name;

        if (e.has_value()) {
            m_name = e.value().firstname + e.value().lastname;
        }
        else {
            m_name = "";
        }

        /*auto d = Department::getDepartment(department_id);

        std::string d_name = d.getName();*/

        std::cout << "| Manager ID       | " << std::setw(38) << std::left << (std::to_string(manager_id) + " (" + m_name + ")") << " |" << std::endl;
        std::cout << "| Department ID    | " << std::setw(38) << std::left << (std::to_string(department_id) + " (" + ")") << " |" << std::endl;

        if (getClassName() == "Emp") {
            std::cout << "+------------------+----------------------------------------+" << std::endl;
        }
        
    }


    virtual const char* getClassName() const {
        return "Emp";
    }

    void getUserInput(){
         setId(stoi(input("Enter Id: ", idRegex)));
         setFirstname(input("Enter first name: "));
         setLastname(input("Enter last name: "));
         setDob(input("Enter DOB (dd-mm-yyyy): ", dateRegex));
         setMobile(input("Enter Mobile Number: ", mobileRegex));
         setEmail(input("Enter Email: ", emailRegex));
         setAddress(input("Enter Adress: "));
         setGender(stringToGender(input("Enter Gender (Male, Female, Other): ")));
         setDoj(input("Enter DOJ (dd-mm-yyyy): ", dateRegex));
         setManagerId(stoi(input("Enter Manager Id: ")));
         setDepartmentId(stoi(input("Enter Department Id: ")));
        
    }

    void getUserInputForUpdate() {

        std::cout << "Please enter the updated values or '#' to keep the value as it is\n";
        auto id{ input("Enter Id: ") };
        if (!(id == "#")) setId(stoi(id));
        
        auto firstname{ input("Enter first name: ") };
        if (!(firstname == "#")) setFirstname(firstname);

        auto lastname{ input("Enter last name: ") };
        if (!(lastname == "#")) setLastname(lastname);

        auto dob{input( "Enter DOB (dd-mm-yyyy): ",dateRegex)};
        if (!(dob == "#")) setDob(dob);

        auto mobile{ input("Enter Mobile Number: ",mobileRegex) };
        if (!(mobile == "#")) setMobile(mobile);

        auto email{ input("Enter Email: ",emailRegex) };
        if (!(email == "#")) setEmail(email);

        auto address{ input("Enter Adress: ") };
        if (!(address == "#")) setAddress(address);

        auto gender{ input("Enter Gender (Male, Female, Other): ") };
        if (!(gender == "#")) setGender(stringToGender(gender));

        auto doJ{ input("Enter DOJ (dd-mm-yyyy): ", dateRegex) };
        if (!(doJ == "#")) setDoj(doJ);

        auto mid{ input("Enter Manager Id: ") };
        if (!(mid == "#")) setManagerId(stoi(mid));

        auto did{ input("Enter Department Id: ") };
        if (!(did == "#")) setDepartmentId(stoi(did));
    }


    static std::optional<Employee> getEmployeeById(int id) {
        DB dbI;
        dbI.open("Rohit.db");

        Employee emp;
        

        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            Employee* emp = static_cast<Employee*>(data);

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

            
            return 0;
        };


        std::string selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(id) + ";";
        dbI.executeSelectQuery(selectQuery.c_str(), callback, &emp, "");

        
        if (emp.getId() == 0) {
            return std::nullopt;
        }
        return emp;
    }


    static std::vector<Employee> getMultipleEmployee(const std::string& queryField = "", const std::string& queryValue = "") {
        DB dbI;
        dbI.open("Rohit.db");


        std::vector<Employee> vecOfEmp;

        std::string selectQuery;


        if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
             selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = " + queryValue + "; ";
            
        }
        else if (queryField == "" && queryValue == "") {
            selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id ;";
        }
        else {
            selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = '" + queryValue + "';";   
        }


        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            std::vector<Employee>* vecOfEmp = static_cast<std::vector<Employee>*>(data);

            Employee emp;

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

            vecOfEmp->push_back(std::move(emp));
            return 0;
            };

        dbI.executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp,"");

        int change = sqlite3_changes(dbI.db);

        if (change == 0) {

        }
        return vecOfEmp;
    }



    bool save() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string  insertQuery = "INSERT INTO Employee "
                                    "(id, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id) VALUES (";

        insertQuery += std::to_string(id) + 
            ",'" + firstname + 
            "','" + lastname + 
            "','" + dob + 
            "','" + mobile + 
            "','" + email + 
            "','" + address + 
            "','" + genderToString(gender) + 
            "','" + doj + 
            "'," + std::to_string(manager_id) + 
            "," + std::to_string(department_id) + ");";

        if (!dbI.executeQuery(insertQuery.c_str(), "")) { return false; }

        return true;
    }

    bool deleteThis() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string deleteQuery = "DELETE FROM Employee WHERE id = ";
        deleteQuery += std::to_string(id);

        if (!dbI.executeQuery(deleteQuery.c_str(), "")) { return false; }

        return true;
    }

    bool update() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string updateQuery = "UPDATE Employee SET ";
        updateQuery +=
                    "firstname='" + firstname + 
                    "', lastname='" + lastname + 
                    "', dob='" + dob +
                    "', mobile='" + mobile + 
                    "', email='" + email + 
                    "', address='" + address + 
                    "', gender='" + genderToString(gender) + 
                    "', doj='" + doj +
                    "', manager_id=" + std::to_string(manager_id) + 
                    ", department_id=" + std::to_string(department_id) + 
                    " WHERE id = " + std::to_string(id) + ";";
       

        if (!dbI.executeQuery(updateQuery.c_str(), "")) return false;

        return true;
    }

private:
    int id{};
    std::string firstname;
    std::string lastname;
    std::string dob;
    std::string mobile;
    std::string email;
    std::string address;
    Gender gender;
    std::string doj;
    int manager_id{};
    int department_id{};
};