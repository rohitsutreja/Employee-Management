#pragma once
#include "Employee.h"

class Manager : public Employee {
public:

    Manager(int id, const std::string& firstname, const std::string& lastname, const std::string& dob,
        const std::string& mobile, const std::string& email, const std::string& address,
        Gender gender, const std::string& doj, float salary, int w_location_id,
        int manager_id, int department_id, int management_experience,
        const std::string& project_title)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, salary,
             manager_id, department_id),
        management_experience(management_experience), project_title(project_title) {}

    int getManagementExperience() const { return management_experience; }
    std::string getProjectTitle() const { return project_title; }

private:

    int management_experience;
    std::string project_title;
};
