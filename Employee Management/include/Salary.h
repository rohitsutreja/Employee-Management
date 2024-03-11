#include <iostream>
#include<iomanip>
#include"Helper.h"
#include "Employee.h"


class Salary {
public:

    Salary() = default;
    Salary(int id, float base_salary, float bonus)
        : id(id), base_salary(base_salary), bonus(bonus), amount(base_salary + bonus) {}

    int getId() const { return id; }

    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    int getBonus() const { return bonus; }

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

    void getUserInput() {
        setBaseSalary(stof(input("Please enter Base Salary: \n")));
        setBonus(stof(input("Please enter Bonus: \n")));
        setAmount(base_salary + bonus);
    }

    void getUserInputForUpdate() {
        auto base = input("Please enter Base Salary: \n");
        if(base!="#") setBaseSalary(stof(base));
        
        auto bon = input("Please enter Bonus: \n");
        if(base!= "#") setBonus(stof(bon));

        setAmount(base_salary + bonus);
    }

    void display() const {

        //auto e = Employee::getEmployeeById(id);

        //std::string name;

        //if (e.has_value()) {
        //    name = e.value().getFirstname() + " " + e.value().getLastname();
        //}
        //else {
        //    name = "";
        //}
        std::cout << "+------------------+----------------------------------------+" << std::endl;
        std::cout << "|\033[32m ID\033[0m               | " << std::setw(38) << std::left << id << " |" << std::endl;
        //std::cout << "| Name             | " << std::setw(38) << std::left << name << " |" << std::endl;
        std::cout << "| Base Salary      | " << std::setw(38) << std::left << base_salary << " |" << std::endl;
        std::cout << "| Bonus            | " << std::setw(38) << std::left << bonus << " |" << std::endl;
        std::cout << "| Total Salary     | " << std::setw(38) << std::left << amount << " |" << std::endl;
        std::cout << "+------------------+----------------------------------------+" << std::endl;
    }

    void increment(int percentage) {
        base_salary = base_salary + (base_salary * percentage) / 100;
        amount = base_salary + bonus;
    }

    static std::optional<Salary> getSalaryByID(int id) {
        DB dbI;
        dbI.open("Rohit.db");

        std::string selectQuery = "SELECT * FROM SALARY WHERE id = " + std::to_string(id) + ";";

        Salary salary;

        auto callback = [](void* data, int argc, char** argv, char** azColName) {
        
            Salary* s = static_cast<Salary*>(data);

            s->setID(std::stoi(argv[0]));
            s->setBaseSalary(std::stof(argv[1]));
            s->setBonus(std::stof(argv[2]));
            s->setAmount(std::stof(argv[1]) + std::stof(argv[2]));


            return 0;
        };

        dbI.executeSelectQuery(selectQuery.c_str(), callback, &salary, "");

        if (salary.getId() == 0) {
            return std::nullopt;
        }
        return salary;
    }

    bool save() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string  insertQuery = "INSERT INTO Salary "
            "(id, base_salary, bonus) VALUES (";

        insertQuery += std::to_string(id) +
            ", " + std::to_string(base_salary) +
            ", " + std::to_string(bonus) +
                 + ");";

        if (!dbI.executeQuery(insertQuery.c_str(), "")) { return false; }

        return true;
    }

    bool update() {
        DB dbI;
        dbI.open("Rohit.db");

        std::string updateQuery = "UPDATE Salary SET ";
        updateQuery +=
            "base_salary= " + std::to_string(base_salary) +
            ",bonus = " + std::to_string(bonus) +
            " WHERE id = " + std::to_string(id) + ";";


        if (!dbI.executeQuery(updateQuery.c_str(), "")) return false;

        return true;
    }


private:
    int id{};
    float base_salary{};
    float bonus{};
    float amount{};
};
