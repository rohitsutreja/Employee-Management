#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include<optional>
#include<iomanip>
#include"DB.h"
#include "Util.h"
#include "Regex.h"
#include"Department.h"
#include"Salary.h"




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
    return "Other";
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

    Employee(int id, std::string_view firstname, std::string_view lastname, std::string_view,
        std::string_view mobile, std::string_view email, std::string_view address,
        Gender gender, std::string_view doj,
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
    void setFirstname(std::string_view firstname) { this->firstname = firstname; }
    void setLastname(std::string_view lastname) { this->lastname = lastname; }
    void setDob(std::string_view dob) { this->dob = dob; }
    void setMobile(std::string_view mobile) { this->mobile = mobile; }
    void setEmail(std::string_view email) { this->email = email; }
    void setAddress(std::string_view address) { this->address = address; }
    void setGender(Gender g) { this->gender = g; }
    void setDoj(std::string_view doj) { this->doj = doj; }
    void setManagerId(int manager_id) { this->manager_id = manager_id; }
    void setDepartmentId(int department_id) { this->department_id = department_id; }
    void setSalary(const Salary& s) { this->salary = s; }

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
        std::cout << "| Salary           | " << std::setw(38) << std::left << salary.getAmount() << " |" << std::endl;

        auto e = Employee::getEmployeeById(manager_id);

        std::string m_name;

        if (e.has_value()) {
            m_name = e.value().getFirstname() + " " + e.value().getLastname() + " (ID - " + std::to_string(manager_id) + ")";
        }
        else {
            m_name = "-";
        }

        auto d = Department::getDepartment(department_id);

        std::string d_name;
        if (d.has_value()) {
            d_name = d.value().getName() + " (ID - " + std::to_string(department_id) + ")";
        }
        else {
            d_name = "-";
        }
       

        std::cout << "| Manager          | " << std::setw(38) << std::left <<  m_name  << " |" << std::endl;
        std::cout << "| Department       | " << std::setw(38) << std::left <<  d_name  << " |" << std::endl;

        if (getClassName() == "Emp") {
            std::cout << "+------------------+----------------------------------------+" << std::endl;
        }
        
    }

    virtual const char* getClassName() const {
        return "Emp";
    }

    void getUserInput(){
         setId(stoi(input("Enter Id: ", idRegex)));
         setFirstname(input("Enter first name: ", nameRegex));
         setLastname(input("Enter last name: "));
         setDob(input("Enter DOB (dd-mm-yyyy): ", dateRegex));
         setMobile(input("Enter Mobile Number: ", mobileRegex));
         setEmail(input("Enter Email: ", emailRegex));
         setAddress(input("Enter Adress: "));
         setGender(stringToGender(input("Enter Gender (Male, Female, Other): ",genderRegex)));
         setDoj(input("Enter DOJ (dd-mm-yyyy): ", dateRegex));

         auto mId = input("Enter Manager Id ('#' to skip): ", idRegex, true);
         if (mId == "#") {
             std::cout << "Got it";
             setManagerId(-1);
         }
         else {
             setManagerId(stoi(mId));
         }
        
         setDepartmentId(stoi(input("Enter Department Id: ",idRegex)));

         salary.setID(id);
         salary.getUserInput();
    }

    void getUserInputForUpdate() {

        //std::cout << "Please enter the updated values or '#' to keep the value as it is\n";
        //auto id{ input("Enter Id: ", idRegex ,true) };
        //if (!(id == "#")) setId(stoi(id));
        //
        auto firstname{ input("Enter first name: ",nameRegex, true) };
        if (!(firstname == "#")) setFirstname(firstname);

        auto lastname{ input("Enter last name: ", {} , true)};
        if (!(lastname == "#")) setLastname(lastname);

        auto dob{ input("Enter DOB (dd-mm-yyyy): ",dateRegex,true) };
        if (!(dob == "#")) setDob(dob);

        auto mobile{ input("Enter Mobile Number: ",mobileRegex,true) };
        if (!(mobile == "#")) setMobile(mobile);

        auto email{ input("Enter Email: ",emailRegex,true) };
        if (!(email == "#")) setEmail(email);

        auto address{ input("Enter Adress: ",{},true) };
        if (!(address == "#")) setAddress(address);

        auto gender{ input("Enter Gender (Male, Female, Other): ", genderRegex, true) };
        if (!(gender == "#")) setGender(stringToGender(gender));

        auto doJ{ input("Enter DOJ (dd-mm-yyyy): ", dateRegex,true) };
        if (!(doJ == "#")) setDoj(doJ);

        auto mid{ input("Enter Manager Id: ",idRegex, true) };
        if (!(mid == "#")) setManagerId(stoi(mid));

        auto did{ input("Enter Department Id: ", idRegex , true) };
        if (!(did == "#")) setDepartmentId(stoi(did));

        salary.setID(getId());
        salary.getUserInputForUpdate();
    }


    static std::optional<Employee> getEmployeeById(int id) {
        auto dbI = DB::getDB();
      

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
        dbI->executeSelectQuery(selectQuery.c_str(), callback, &emp, "Employee selected with ID " + std::to_string(id));
       
        if (emp.getId() == 0) {
            return std::nullopt;
        }

        emp.salary = Salary::getSalaryByID(id).value();

        return emp;
    }


    static std::vector<Employee> getMultipleEmployee(const std::string& queryField = "", const std::string& queryValue = "") {
        auto dbI = DB::getDB();


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
            emp.setSalary((Salary::getSalaryByID(std::stoi(argv[0])).value()));

            vecOfEmp->push_back(std::move(emp));
            return 0;
            };

        dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp,"Multiple Employee selected.");

     
        return vecOfEmp;
    }



    bool save() {
        auto dbI = DB::getDB();


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

        if (!dbI->executeQuery(insertQuery.c_str(), "An Employee Inserted with ID: " + std::to_string(id))) {
            return false; 
        }

        salary.save();

        return true;
    }

    bool deleteThis() {
        auto dbI = DB::getDB();


        std::string deleteQuery = "DELETE FROM Employee WHERE id = ";
        deleteQuery += std::to_string(id);

        return dbI->executeQuery(deleteQuery.c_str(),"Employee Deleted with ID: " + std::to_string(id)) && salary.deleteThis();
    }

    bool update() {
        auto dbI = DB::getDB();


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
       

        if (!dbI->executeQuery(updateQuery.c_str(), "Employee Updated with ID: " + std::to_string(id))) return false;

        salary.update();

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
    Gender gender{Gender::Other};
    std::string doj;
    int manager_id{};
    int department_id{};
    Salary salary;
};