#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include <optional>
#include <iomanip>
#include "../DB.h"
#include "../Util.h"
#include "../Regex.h"
#include "Department.h"
#include "Salary.h"

class Employee {

public:
    enum class Gender { Male, Female, Other };

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

    bool display() const;

    virtual const char* getClassName() const;

    bool getUserInput();
    bool getUserInputForUpdate();

    static std::optional<Employee> getEmployeeById(int id);
    static std::vector<Employee> getMultipleEmployee(const std::string& queryField = "", const std::string& queryValue = "");
    bool save();
    bool deleteThis();
    bool update();


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


protected:
    static std::string genderToString(Gender g) {
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


    static Gender stringToGender(std::string_view s) {
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

};