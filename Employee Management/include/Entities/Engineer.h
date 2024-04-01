#pragma once
#include "Employee.h"

namespace Entity {
    class Engineer : public Employee {
    public:
        Engineer() = default;

        static std::optional<Engineer> getEngineerById(int id);
        static std::vector<Engineer> getMultipleEngineers(const std::string& queryField = "", const std::string& queryValue = "");
        bool save() const;
        bool update() const;
        bool deleteThis() const;

        bool populateForInsertion() noexcept;
        bool populateForUpdation() noexcept;
        void display() const;
        
        const char* getClassName() const override;

        const std::string& getProgrammingLanguage() const { return programming_language; }
        const std::string& getSpecialization() const { return specialization; }

        bool setProgrammingLanguage(std::string_view programming_language) {
            this->programming_language = programming_language;
            return true;
        }
        bool setSpecialization(std::string_view specialization) {
            this->specialization = specialization;
            return true;
        }

    private:
        std::string programming_language;
        std::string specialization;

    };

}
