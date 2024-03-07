
#include "Employee.h"
class Engineer : public Employee {
public:
    Engineer() = default;

    Engineer(int id, const std::string& firstname, const std::string& lastname, const std::string& dob,
        const std::string& mobile, const std::string& email, const std::string& address,
        Gender gender, const std::string& doj, float salary, int w_location_id,
        int manager_id, int department_id, const std::string& programming_language,
        const std::string& specialization)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, salary,
            manager_id, department_id),
        programming_language(programming_language), specialization(specialization) {}


    std::string getProgrammingLanguage() const { return programming_language; }
    std::string getSpecialization() const { return specialization; }

    void setProgrammingLanguage(const std::string& programming_language) {
        this->programming_language = programming_language;
    }
    void setSpecialization(const std::string& specialization) {
        this->specialization = specialization;
    }

    const char* getClassName() const override {
        return "Eng";
    }

    void getUserInputForUpdate() {

        Employee::getUserInputForUpdate();

        auto pl{ input("Enter Programming Language: ",emailRegex) };
        if (!(pl == "#")) setProgrammingLanguage(pl);

        auto sp{ input("Enter specialization: ") };
        if (!(sp == "#")) setSpecialization(sp);

    }

    void getUserInput() {
        Employee::getUserInput();
        setProgrammingLanguage(input("Enter programming_language name: "));
        setSpecialization(input("Enter specialization: "));
    }

    void display() {
        Employee::display();

        std::cout << "| Prog. Language   | " << std::setw(38) << std::left << programming_language << " |" << std::endl;
        std::cout << "| Specialization   | " << std::setw(38) << std::left << specialization << " |" << std::endl;
        std::cout << "+------------------+----------------------------------------+" << std::endl;
    }

    bool save(){
        DB dbI;
        dbI.open("Rohit.db");

        Employee::save();

        std::string insertQuery = "INSERT INTO Engineer VALUES (" + std::to_string(Employee::getId()) + ",'" + programming_language + "', '" + specialization + "');";

        if (!dbI.executeQuery(insertQuery.c_str(), "")) { return false; }
        return true;
    }

    bool deleteThis() {
        DB dbI;
        dbI.open("Rohit.db");
        
        Employee::deleteThis();

        std::string deleteQuery = "DELETE FROM Engineer WHERE id = ";
        deleteQuery += std::to_string(getId());

        if (!dbI.executeQuery(deleteQuery.c_str(), "")) { return false; }

        return true;
    }

    bool update() {
        DB dbI;
        dbI.open("Rohit.db");

        Employee::update();

        std::string updateQuery = "UPDATE Engineer SET ";
        updateQuery +=
            "programming_language='" + programming_language +
            "', specialization='" + specialization +
            " WHERE id = " + std::to_string(getId()) + ";";


        if (!dbI.executeQuery(updateQuery.c_str(), "")) return false;

        return true;
    }

    static Engineer getEngineerByID(int id) {
        DB dbI;
        dbI.open("Rohit.db");

        Engineer e;

        std::string selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id WHERE Employee.id = " + std::to_string(id) + ";";

        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            Engineer* emp = static_cast<Engineer*>(data);

            emp->setId(std::stoi(argv[0]));
            emp->setFirstname(argv[1]);
            emp->setLastname(argv[2]);
            emp->setDob(argv[3]);
            emp->setMobile(argv[4]);
            emp->setEmail(argv[5]);
            emp->setAddress(argv[6]);
            emp->setGender(stringToGender(argv[7]));
            emp->setDoj(argv[8]);
            emp->setManagerId(std::stoi(argv[9]));
            emp->setDepartmentId(std::stoi(argv[10]));
            emp->setProgrammingLanguage(argv[12]);
            emp->setSpecialization(argv[13]);

            return 0;
        };
       
        dbI.executeSelectQuery(selectQuery.c_str(), callback, &e, "");
       
        return e;
    }

    static std::vector<Engineer> getMultipleEngineers(const std::string& queryField = "", const std::string& queryValue = "") {
        DB dbI;
        dbI.open("Rohit.db");

        std::vector<Engineer> vecOfEmp;

        std::string selectQuery;


        if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
            selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = " + queryValue + "; ";

        }
        else if (queryField == "" && queryValue == "") {
            selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id JOIN Department ON Employee.department_id = Department.id ;";
        }
        else {
            selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = '" + queryValue + "';";
        }


        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            std::vector<Engineer>* vecOfEmp = static_cast<std::vector<Engineer>*>(data);

            Engineer emp;

            emp.setId(std::stoi(argv[0]));
            emp.setFirstname(argv[1]);
            emp.setLastname(argv[2]);
            emp.setDob(argv[3]);
            emp.setMobile(argv[4]);
            emp.setEmail(argv[5]);
            emp.setAddress(argv[6]);
            emp.setGender(stringToGender(argv[7]));
            emp.setDoj(argv[8]);
            emp.setManagerId(std::stoi(argv[9]));
            emp.setDepartmentId(std::stoi(argv[10]));
            emp.setProgrammingLanguage(argv[12]);
            emp.setSpecialization(argv[13]);

            vecOfEmp->push_back(std::move(emp));
            return 0;
            };

        dbI.executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "");

        return vecOfEmp;
    }

private:
    std::string programming_language;
    std::string specialization;
    
};
