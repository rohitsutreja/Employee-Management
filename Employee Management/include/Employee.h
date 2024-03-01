#include <iostream>
#include <string>

enum class Gender { Male, Female, Other };

class Employee {

public:
    Employee() = default;
    Employee(int id, const std::string& firstname, const std::string& lastname, const std::string& dob,
        const std::string& mobile, const std::string& email, const std::string& address,
        Gender gender, const std::string& doj, int w_location_id,
        int manager_id, int department_id)
        : id(id), firstname(firstname), lastname(lastname), dob(dob), mobile(mobile), email(email),
        address(address), gender(gender), doj(doj),  w_location_id(w_location_id),
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
    int getWLocationId() const { return w_location_id; }
    int getManagerId() const { return manager_id; }
    int getDepartmentId() const { return department_id; }


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
    int w_location_id;
    int manager_id;
    int department_id;
};
