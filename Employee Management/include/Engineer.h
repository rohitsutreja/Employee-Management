
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
        auto dbI = DB::getDB();

        Employee::save();

        std::string insertQuery = "INSERT INTO Engineer VALUES (" + std::to_string(getId()) + ",'" + programming_language + "', '" + specialization + "');";

        if (!dbI->executeQuery(insertQuery.c_str(), "An Engineer Inserted with ID : " + std::to_string(getId()) + ".")) { return false; }
        return true;
    }

    bool deleteThis() {
        auto dbI = DB::getDB();

        Employee::deleteThis();

        std::string deleteQuery = "DELETE FROM Engineer WHERE id = ";
        deleteQuery += std::to_string(getId());

        if (!dbI->executeQuery(deleteQuery.c_str(), "Engineer Deleted with ID: " + std::to_string(getId()) + ".")) { return false; }

        return true;
    }

    bool update() {
        auto dbI = DB::getDB();

        Employee::update();

        std::string updateQuery = "UPDATE Engineer SET ";
        updateQuery +=
            "programming_language='" + programming_language +
            "', specialization='" + specialization +
            "' WHERE id = " + std::to_string(getId()) + ";";


        if (!dbI->executeQuery(updateQuery.c_str(), "Engineer Updated with ID: " + std::to_string(getId()) + ".")) return false;

        return true;
    }

    static std::optional<Engineer> getEngineerByID(int id) {
        auto dbI = DB::getDB();


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
            emp->setSalary(Salary::getSalaryByID(std::stoi(argv[0])).value());

            return 0;
        };
       
        dbI->executeSelectQuery(selectQuery.c_str(), callback, &e, "Engineer selected with ID " + std::to_string(id) + ".");

        if (e.getId() != 0) {
            
            return e;
        }
      
       
        return {};
    }

    static std::vector<Engineer> getMultipleEngineers(const std::string& queryField = "", const std::string& queryValue = "") {
        auto dbI = DB::getDB();


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

            emp.setSalary(Salary::getSalaryByID(std::stoi(argv[0])).value());

            vecOfEmp->push_back(std::move(emp));
            return 0;
            };

        dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "Multiple Engineers salected.");

        return vecOfEmp;
    }

private:
    std::string programming_language;
    std::string specialization;
    
};
