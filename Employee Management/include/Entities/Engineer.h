#pragma once
#include "Employee.h"

class Engineer : public Employee {
public:
    Engineer() = default;

    std::string getProgrammingLanguage() const { return programming_language; }
    std::string getSpecialization() const { return specialization; }

    void setProgrammingLanguage(std::string_view programming_language) {
        this->programming_language = programming_language;
    }
    void setSpecialization(std::string_view specialization) {
        this->specialization = specialization;
    }

    const char* getClassName() const override;

    bool getUserInputForUpdate();
    bool getUserInput();

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
