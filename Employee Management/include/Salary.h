#include <iostream>

class Salary {
public:

    Salary() = default;
    Salary(int id, int emp_id, float amount, float base_salary, const std::string& date, int bonus)
        : id(id), amount(amount), base_salary(base_salary), date(date), bonus(bonus) {}

    int getId() const { return id; }

    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    std::string getDate() const { return date; }
    int getBonus() const { return bonus; }

private:

    int id;
    float amount;
    float base_salary;
    std::string date;
    int bonus;
};
