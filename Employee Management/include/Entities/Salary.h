#ifndef SALARY_H
#define SALARY_H

#include <iostream>
#include<iomanip>
#include"../Util.h"
#include "../DB.h"

namespace Entity {

    class Salary {
    public:
        Salary() = default;

        static std::optional<Salary> getSalaryByID(int id);
        static std::vector<Salary> getMultipleSalary(const std::string& queryField = "", const std::string& queryValue = "");
        bool save() const;
        bool update() const;
        bool deleteThis() const;

        bool populateForInsertion() noexcept;
        bool populateForUpdation() noexcept;
        void display() const;

        double increment(int percentage);
        double computeSalary() const;

        int getId() const { return id; }
        double getBaseSalary() const { return base_salary; }
        double getBonus() const { return bonus; }

        bool setID(int id) {
            if (id >= -1 && id < 1000000) {
                this->id = id;
                return true;
            }
            return false;
        }
        bool setBaseSalary(double base_salary) {
            this->base_salary = base_salary; 
            return true;
        }
        bool setBonus(double bonus) {
            this->bonus = bonus; 
            return true;
        }

    private:
        int id{};
        double base_salary{};
        double bonus{};
        double amount{};
    };

}

#endif