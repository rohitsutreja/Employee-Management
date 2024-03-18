#ifndef SALARY_H
#define SALARY_H

#include <iostream>
#include<iomanip>
#include"Util.h"
#include "DB.h"

class Salary {
public:

    Salary() = default;
    Salary(int id, float base_salary, float bonus)
        : id(id), base_salary(base_salary), bonus(bonus), amount(base_salary + bonus) {}

    int getId() const { return id; }

    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    float getBonus() const { return bonus; }

    void setAmount(float amount) {
        this->amount = amount;
    }
    void setBaseSalary(float base_salary) {
        this->base_salary = base_salary;
    }
    void setBonus(float bonus) {
        this->bonus = bonus;
    }
    void setID(int id) {
        this->id = id;
    }

    void getUserInput();
    void getUserInputForUpdate();

    void display() const;

    void increment(int percentage);

    static std::optional<Salary> getSalaryByID(int id);
    static std::vector<Salary> getMultipleSalary(const std::string& queryField = "", const std::string& queryValue = "");

    bool save();
    bool update();
    bool deleteThis();

private:
    int id{};
    float base_salary{};
    float bonus{};
    float amount{};
};


#endif