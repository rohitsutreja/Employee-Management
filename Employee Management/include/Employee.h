#include <iostream>
#include <string>
#include"DB.h"
#include "Helper.h"
#include "Regex.h"

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
        std::cout << "ID: " << id << std::endl;
        std::cout << "First Name: " << firstname << std::endl;
        std::cout << "Last Name: " << lastname << std::endl;
        std::cout << "Date of Birth: " << dob << std::endl;
        std::cout << "Mobile: " << mobile << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << "Gender: " << genderToString(gender) << std::endl;
        std::cout << "Date of Joining: " << doj << std::endl;
        std::cout << "Manager ID: " << manager_id << std::endl;
        std::cout << "Department ID: " << department_id << std::endl;
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

    static Employee getEmployee(int id) {
        DB dbI;
        dbI.open("Rohit.db");

        Employee emp;

        std::string selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(id) + ";";
        dbI.executeSelectQuery(selectQuery.c_str(), selectCallback, &emp);
        return emp;
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

        if (!dbI.executeQuery(insertQuery.c_str(), "Inserted Successfully\n")) { return false; }

        return true;
    }

    bool deleteThis() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string deleteQuery = "DELETE FROM Employee WHERE id = ";
        deleteQuery += std::to_string(id);

        if (!dbI.executeQuery(deleteQuery.c_str(), "Deleted Successfully\n")) { return false; }

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
       

        if (!dbI.executeQuery(updateQuery.c_str(), "Updated Successfully\n")) return false;

        return true;
    }

private:
    int id;
    std::string firstname;
    std::string lastname;
    std::string dob;
    std::string mobile;
    std::string email;
    std::string address;
    Gender gender;
    std::string doj;
    int manager_id;
    int department_id;

    static int selectCallback(void* data, int argc, char** argv, char** azColName) {
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
    }

};