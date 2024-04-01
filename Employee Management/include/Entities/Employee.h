#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include <optional>
#include <iomanip>
#include "../DB.h"
#include "../Util.h"
#include "Department.h"
#include "Salary.h"

namespace Entity {

    class Employee {

    public:
        enum class Gender { Male, Female, Other };

    public:
        Employee() = default;

        static std::optional<Employee> getEmployeeById(int id);
        static std::vector<Employee> getMultipleEmployee(const std::string& queryField = "", const std::string& queryValue = "");
        bool save() const;
        bool deleteThis() const;
        bool update() const;

        bool display() const;
        bool populateForInsertion() noexcept;
        bool populateForUpdation() noexcept;

        virtual const char* getClassName() const;

        int getId() const { return id; }
        const std::string& getFirstname() const { return firstname; }
        const std::string& getLastname() const { return lastname; }
        const std::string& getDob() const { return dob; }
        const std::string& getMobile() const { return mobile; }
        const std::string& getEmail() const { return email; }
        const std::string& getAddress() const { return address; }
        const std::string& getDoj() const { return doj; }
        Gender getGender() const { return gender; }
        int getManagerId() const { return manager_id; }
        int getDepartmentId() const { return department_id; }


        bool setId(int id) {
            if (id >= -1 && id < 1000000) {
                this->id = id;
                return true;
            }
            return false;
        }
        bool setFirstname(const std::string& firstname) {
            if (!firstname.empty() && !std::regex_match(firstname, nameRegex)) {
                return false;
            }
            this->firstname = firstname;
            return true;

        }
        bool setLastname(const std::string& lastname) {
            if (!lastname.empty() && !std::regex_match(lastname, nameRegex)) {
                return false;
            }
            this->lastname = lastname;
            return true;
        }
        bool setDob(const std::string& dob) {
            if (!dob.empty() && !std::regex_match(dob, dateRegex)) {
                return false;
            }
            this->dob = dob;
            return true;

        }
        bool setMobile(const std::string& mobile) {
            if (!mobile.empty() && !std::regex_match(mobile, mobileRegex)) {
                return false;
            }
            this->mobile = mobile;
            return true;

        }
        bool setEmail(const std::string& email) {
            if (!email.empty() && !std::regex_match(email, emailRegex)) {
                return false;
            }
            this->email = email;
            return true;
        }
        bool setAddress(const std::string& address) {
            this->address = address;
            return true;
        }
        bool setGender(Gender g) {
            if (!std::regex_match(genderToString(g), genderRegex)) {
                return false;
            }
            this->gender = g;
            return true;
        }
        bool setDoj(const std::string& doj) {
            if (!dob.empty() && !std::regex_match(dob, dateRegex)) {
                return false;
            }
            this->doj = doj;
            return true;
        }
        bool setManagerId(int manager_id) {
            if (manager_id >= -1 && manager_id < 1000000) {
                this->manager_id = manager_id;
                return true;
            }
            return false;
        }
        bool setDepartmentId(int department_id) {
            if (department_id >= -1 && department_id < 1000000) {
                this->department_id = department_id;
                return true;
            }
            return false;
        }
        bool setSalary(const Salary& s) {
            this->salary = s;
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
        Gender gender{ Gender::Other };
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

            default:
                return "Other";
            }
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
}