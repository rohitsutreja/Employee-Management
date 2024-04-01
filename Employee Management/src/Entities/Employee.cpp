#include "../../include/Entities/Employee.h"


namespace Entity {

    std::optional<Employee> Employee::getEmployeeById(int id) {
        auto dbI = DB::getDB();

        Employee employee;

        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            Employee* employee = static_cast<Employee*>(data);

            employee->setId(argv[0] ? std::stoi(argv[0]) : -1);
            employee->setFirstname(argv[1] ? argv[1] : "");
            employee->setLastname(argv[2] ? argv[2] : "");
            employee->setDob(argv[3] ? argv[3] : "");
            employee->setMobile(argv[4] ? argv[4] : "");
            employee->setEmail(argv[5] ? argv[5] : "");
            employee->setAddress(argv[6] ? argv[6] : "");
            employee->setGender(argv[7] ? stringToGender(argv[7]) : Gender::Other);
            employee->setDoj(argv[8] ? argv[8] : "");
            employee->setManagerId(argv[9] ? std::stoi(argv[9]) : -1);

            employee->setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);

            return 0;
            };

        std::string selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(id) + ";";

        try {
            dbI->executeSelectQuery(selectQuery.c_str(), callback, &employee, "Employee selected with ID " + std::to_string(id));
        }
        catch (...) {
            return std::nullopt;
        }


        if (employee.getId() == 0) {
            return std::nullopt;
        }

        if (auto salary = Salary::getSalaryByID(employee.id); salary) {
            employee.setSalary(std::move(*salary));
        }

        return employee;
    }

    std::vector<Employee> Employee::getMultipleEmployee(const std::string& queryField, const std::string& queryValue) {
        auto dbI = DB::getDB();

        std::vector<Employee> vecOfEmp;

        std::string selectQuery;


        if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
            selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = " + queryValue + " COLLATE NOCASE; ";
        }
        else if (queryField == "" && queryValue == "") {
            selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id COLLATE NOCASE;";
        }
        else {
            selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = '" + queryValue + "' COLLATE NOCASE;";
        }


        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            std::vector<Employee>* vecOfEmp = static_cast<std::vector<Employee>*>(data);

            Employee employee;

            employee.setId(argv[0] ? std::stoi(argv[0]) : -1);
            employee.setFirstname(argv[1] ? argv[1] : "");
            employee.setLastname(argv[2] ? argv[2] : "");
            employee.setDob(argv[3] ? argv[3] : "");
            employee.setMobile(argv[4] ? argv[4] : "");
            employee.setEmail(argv[5] ? argv[5] : "");
            employee.setAddress(argv[6] ? argv[6] : "");
            employee.setGender(argv[7] ? stringToGender(argv[7]) : Gender::Other);
            employee.setDoj(argv[8] ? argv[8] : "");
            employee.setManagerId(argv[9] ? std::stoi(argv[9]) : -1);
            employee.setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);

            if (auto salary = Salary::getSalaryByID(employee.id); salary) {
                employee.setSalary(std::move(*salary));
            }

            vecOfEmp->push_back(std::move(employee));
            return 0;
            };

        try {
            dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "Multiple Employee selected.");
        }
        catch (...) {
            return {};
        }


        return vecOfEmp;
    }

    bool Employee::save() const {
        auto dbI = DB::getDB();

        std::string  insertQuery = "INSERT INTO Employee "
            "(id, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id) VALUES (";

        insertQuery += std::to_string(id) +
            ",'" + firstname +
            "','" + lastname +
            "','" + dob +
            "','" + mobile +
            "','" + email +
            "','" + address +
            "','" + genderToString(gender) +
            "','" + doj +
            "'," + (manager_id == -1 ? "NULL" : std::to_string(manager_id)) +
            "," + std::to_string(department_id) + ");";

        if (!dbI->executeQuery(insertQuery.c_str(), "An Employee Inserted with ID: " + std::to_string(id))) {
            return false;
        }

        salary.save();

        return true;
    }

    bool Employee::update() const {
        auto dbI = DB::getDB();


        std::string updateQuery = "UPDATE Employee SET ";
        updateQuery +=
            "firstname='" + firstname +
            "', lastname='" + lastname +
            "', dob='" + dob +
            "', mobile='" + mobile +
            "', email='" + email +
            "', address='" + address +
            "', gender='" + genderToString(gender) +
            "', doj='" + doj +
            "', manager_id=" + (manager_id == -1 ? "NULL" : std::to_string(manager_id)) +
            ", department_id=" + std::to_string(department_id) +
            " WHERE id = " + std::to_string(id) + ";";


        if (!dbI->executeQuery(updateQuery.c_str(), "Employee Updated with ID: " + std::to_string(id))) return false;

        if (dbI->noOfRowChanged() == 0) return false;

        salary.update();

        return true;
    }

    bool Employee::deleteThis() const {
        auto dbI = DB::getDB();

        std::string deleteQuery1 = "DELETE FROM Manager WHERE id = " + std::to_string(id);
        std::string deleteQuery2 = "DELETE FROM Engineer WHERE id = " + std::to_string(id);

        salary.deleteThis();

        dbI->executeQuery(deleteQuery1.c_str());
        dbI->executeQuery(deleteQuery2.c_str());

        std::string deleteQuery = "DELETE FROM Employee WHERE id = " + std::to_string(id);

        if (!dbI->executeQuery(deleteQuery.c_str(), " Employee Deleted with Id: " + std::to_string(id))) {
            return false;
        }

        if (dbI->noOfRowChanged() == 0) { return false; }

        return true;
    }

    bool Employee::getUserInput() noexcept {
        try {
            std::cout << "- Insert employee details\n\n";
            std::cout << "- Enter ':q' at any point to cancel insertion\n\n";


            setId(stoi(inputWithQuit("\nEnter Id (Max - 6 digits): ", idRegex)));
            setFirstname(inputWithQuit("\nEnter first name: ", nameRegex));
            setLastname(inputWithQuit("\nEnter last name: "));
            setDob(inputWithQuit("\nEnter DOB (dd-mm-yyyy): ", dateRegex));
            setMobile(inputWithQuit("\nEnter Mobile Number ( 10 digit ): ", mobileRegex));
            setEmail(inputWithQuit("\nEnter Email: ", emailRegex));
            setAddress(inputWithQuit("\nEnter Adress: "));
            setGender(stringToGender(inputWithQuit("\nEnter Gender (Male, Female, Other): ", genderRegex)));
            setDoj(inputWithQuit("\nEnter DOJ (dd-mm-yyyy): ", dateRegex));

            auto mId = inputWithQuit("\nEnter Manager Id (Max - 6 digits) ('#' to skip): ", idRegex, true);
            if (mId == "#") {
                setManagerId(-1);
            }
            else {
                setManagerId(stoi(mId));
            }

            setDepartmentId(stoi(inputWithQuit("\nEnter Department Id (Max - 6 digits): ", idRegex)));

            salary.setID(id);

            return  salary.getUserInput();

        }
        catch (...) {
            *this = Employee();
            return false;
        }
    }

    bool Employee::getUserInputForUpdate() noexcept {
        try {
            std::cout << "- Update details of an employee with id: " << id << "\n\n";
            std::cout << "- Enter ':q' at any point to cancel updation\n\n";
            std::cout << "- Enter '#' to keep the value as it is.\n\n";

            auto firstname{ inputWithQuit("Enter first name: ",nameRegex, true) };
            if (firstname != "#") setFirstname(firstname);

            auto lastname{ inputWithQuit("Enter last name: ", {} , true) };
            if (lastname != "#") setLastname(lastname);

            auto dob{ inputWithQuit("Enter DOB (dd-mm-yyyy): ",dateRegex,true) };
            if (dob != "#") setDob(dob);

            auto mobile{ inputWithQuit("Enter Mobile Number (10 digits): ",mobileRegex,true) };
            if (mobile != "#") setMobile(mobile);

            auto email{ inputWithQuit("Enter Email: ",emailRegex,true) };
            if (email != "#") setEmail(email);

            auto address{ inputWithQuit("Enter Adress: ",{},true) };
            if (address != "#") setAddress(address);

            auto gender{ inputWithQuit("Enter Gender (Male, Female, Other): ", genderRegex, true) };
            if (gender != "#") setGender(stringToGender(gender));

            auto doJ{ inputWithQuit("Enter DOJ (dd-mm-yyyy): ", dateRegex,true) };
            if (doJ != "#") setDoj(doJ);

            auto mid{ inputWithQuit("Enter Manager Id (Max - 6 digits): ",idRegex, true) };
            if (mid != "#") setManagerId(stoi(mid));

            auto did{ inputWithQuit("Enter Department Id (Max - 6 digits): ", idRegex , true) };
            if (did != "#") setDepartmentId(stoi(did));

            salary.setID(getId());

            return salary.getUserInputForUpdate();

        }
        catch (...) {
            *this = Employee();
            return false;
        }


    }

    bool Employee::display() const {
        std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
        std::cout << "|\033[32m ID\033[0m                         | " << std::setw(48) << std::left << id << " |" << std::endl;
        std::cout << "| First Name                 | " << std::setw(48) << std::left << firstname << " |" << std::endl;
        std::cout << "| Last Name                  | " << std::setw(48) << std::left << lastname << " |" << std::endl;
        std::cout << "| Date of Birth              | " << std::setw(48) << std::left << dob << " |" << std::endl;
        std::cout << "| Mobile                     | " << std::setw(48) << std::left << mobile << " |" << std::endl;
        std::cout << "| Email                      | " << std::setw(48) << std::left << email << " |" << std::endl;
        std::cout << "| Address                    | " << std::setw(48) << std::left << address << " |" << std::endl;
        std::cout << "| Gender                     | " << std::setw(48) << std::left << genderToString(gender) << " |" << std::endl;
        std::cout << "| Date of Joining            | " << std::setw(48) << std::left << doj << " |" << std::endl;
        std::cout << "| Salary                     | " << std::setw(48) << std::left << salary.computeSalary() << " |" << std::endl;



        std::string m_name = "-";
        if (manager_id != -1) {
            if (auto employee = Employee::getEmployeeById(manager_id); employee) {
                m_name = employee->getFirstname() + " " + employee->getLastname() + " (ID - " + std::to_string(manager_id) + ")";
            }
        }



        std::string d_name = "-";
        if (auto department = Department::getDepartmentById(department_id); department) {
            d_name = department->getName() + " (ID - " + std::to_string(department_id) + ")";
        }



        std::cout << "| Manager                    | " << std::setw(48) << std::left << m_name << " |" << std::endl;
        std::cout << "| Department                 | " << std::setw(48) << std::left << d_name << " |" << std::endl;

        if (getClassName() == "Emp") {
            std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
        }

        return true;
    }

    const char* Employee::getClassName() const {
        return "Emp";
    }

}