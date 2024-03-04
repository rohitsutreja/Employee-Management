#include <iostream>
#include <string>
#include"DB.h"



enum class Gender { Male, Female, Other };

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
        std::cout << "Gender: " << "Male" << std::endl;
        std::cout << "Date of Joining: " << doj << std::endl;
        std::cout << "Manager ID: " << manager_id << std::endl;
        std::cout << "Department ID: " << department_id << std::endl;
    }

    void getUserInput(){}

    bool save() {}

    bool deleteOne() {}

    static Employee getEmployee(int id) {

    }

    bool update() {

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
};