#include "Employee.h"

class Engineer : public Employee {
public:
    Engineer() = default;

    Engineer(int id, std::string_view firstname, std::string_view lastname, std::string_view dob,
        std::string_view mobile, std::string_view email, std::string_view address,
        Gender gender, std::string_view doj, float salary, int w_location_id,
        int manager_id, int department_id, std::string_view programming_language,
        std::string_view specialization)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, 
            manager_id, department_id),
        programming_language(programming_language), specialization(specialization) {}


    std::string getProgrammingLanguage() const { return programming_language; }
    std::string getSpecialization() const { return specialization; }

    void setProgrammingLanguage(std::string_view programming_language) {
        this->programming_language = programming_language;
    }
    void setSpecialization(std::string_view specialization) {
        this->specialization = specialization;
    }

    const char* getClassName() const override;

    void getUserInputForUpdate();
    void getUserInput();

    void display() const;

    bool save();
    bool deleteThis();
    bool update();
    static std::optional<Engineer> getEngineerById(int id);
    static std::vector<Engineer> getMultipleEngineers(const std::string& queryField = "", const std::string& queryValue = "");

private:
    std::string programming_language;
    std::string specialization;
    
};
