#ifndef DEPARTMENT_H
#define DEPARTMENT_H


#include <iostream>
#include <string>
#include "../Util.h"
#include "../DB.h"
#include "Employee.h"

namespace Entity {

    class Department {
    public:
        Department() = default;

        static std::optional<Department> getDepartmentById(int id);
        static std::vector<Department> getMultipleDepartment(const std::string& queryField = "", const std::string& queryValue = "");
        bool save() const;
        bool update() const;
        bool deleteThis() const;
        
        void display() const;
        bool populateForInsertion() noexcept;
        bool populateForUpdation() noexcept;

        int getId() const { return id; }
        const std::string& getName() const { return name; }
        int getManagerId() const { return manager_id; }
        const std::string& getDescription() const { return description; }

        bool setId(int id) {
            if (id >= -1 && id < 1000000) {
                this->id = id;
                return true;
            }
            return false;
        }
        bool setName(const std::string& name) {
            this->name = name;
            return false;
        }
        bool setManagerId(int manager_id) {
            if (id >= -1 && id < 1000000) {
                this->manager_id = manager_id;
                return true;
            }
            return false;
        }
        bool setDescription(const std::string& description) {
            this->description = description;
            return true;
        }

    private:
        int id{};
        std::string name;
        int manager_id{};
        std::string description;
    };

}

#endif

