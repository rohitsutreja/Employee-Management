#include "../../include/Entities/Employee.h"

bool Employee::display() const {
    std::cout << "+------------------+----------------------------------------+" << std::endl;
    std::cout << "|\033[32m ID\033[0m               | " << std::setw(38) << std::left << id << " |" << std::endl;
    std::cout << "| First Name       | " << std::setw(38) << std::left << firstname << " |" << std::endl;
    std::cout << "| Last Name        | " << std::setw(38) << std::left << lastname << " |" << std::endl;
    std::cout << "| Date of Birth    | " << std::setw(38) << std::left << dob << " |" << std::endl;
    std::cout << "| Mobile           | " << std::setw(38) << std::left << mobile << " |" << std::endl;
    std::cout << "| Email            | " << std::setw(38) << std::left << email << " |" << std::endl;
    std::cout << "| Address          | " << std::setw(38) << std::left << address << " |" << std::endl;
    std::cout << "| Gender           | " << std::setw(38) << std::left << genderToString(gender) << " |" << std::endl;
    std::cout << "| Date of Joining  | " << std::setw(38) << std::left << doj << " |" << std::endl;
    std::cout << "| Salary           | " << std::setw(38) << std::left << salary.getAmount() << " |" << std::endl;

    auto employee = Employee::getEmployeeById(manager_id);

    std::string m_name;

    if (employee) {
        m_name = employee->getFirstname() + " " + employee->getLastname() + " (ID - " + std::to_string(manager_id) + ")";
    }
    else {
        m_name = "-";
    }

    auto department = Department::getDepartmentById(department_id);

    std::string d_name;
    if (department) {
        d_name = department->getName() + " (ID - " + std::to_string(department_id) + ")";
    }
    else {
        d_name = "-";
    }


    std::cout << "| Manager          | " << std::setw(38) << std::left << m_name << " |" << std::endl;
    std::cout << "| Department       | " << std::setw(38) << std::left << d_name << " |" << std::endl;

    if (getClassName() == "Emp") {
        std::cout << "+------------------+----------------------------------------+" << std::endl;
    }

    return true;
}

const char* Employee::getClassName() const {
    return "Emp";
}

bool Employee::getUserInput() {
    try {
        setId(stoi(input("Enter Id: ", idRegex)));
        setFirstname(input("Enter first name: ", nameRegex));
        setLastname(input("Enter last name: "));
        setDob(input("Enter DOB (dd-mm-yyyy): ", dateRegex));
        setMobile(input("Enter Mobile Number: ", mobileRegex));
        setEmail(input("Enter Email: ", emailRegex));
        setAddress(input("Enter Adress: "));
        setGender(stringToGender(input("Enter Gender (Male, Female, Other): ", genderRegex)));
        setDoj(input("Enter DOJ (dd-mm-yyyy): ", dateRegex));

        auto mId = input("Enter Manager Id ('#' to skip): ", idRegex, true);
        if (mId == "#") {
            setManagerId(-1);
        }
        else {
            setManagerId(stoi(mId));
        }

        setDepartmentId(stoi(input("Enter Department Id: ", idRegex)));

        salary.setID(id);

        return  salary.getUserInput();

    }
    catch (...) {
        return false;
    }
}

bool Employee::getUserInputForUpdate() {

    std::cout << "Updating detail for employee with id: " + std::to_string(id);
    std::cout << "\n\nPlease enter the updated values or '#' to keep the value as it is\n\n";

    auto firstname{ input("Enter first name: ",nameRegex, true) };
    if (firstname != "#") setFirstname(firstname);

    auto lastname{ input("Enter last name: ", {} , true) };
    if (lastname != "#") setLastname(lastname);

    auto dob{ input("Enter DOB (dd-mm-yyyy): ",dateRegex,true) };
    if (dob != "#") setDob(dob);

    auto mobile{ input("Enter Mobile Number: ",mobileRegex,true) };
    if (mobile != "#") setMobile(mobile);

    auto email{ input("Enter Email: ",emailRegex,true) };
    if (email != "#") setEmail(email);

    auto address{ input("Enter Adress: ",{},true) };
    if (address != "#") setAddress(address);

    auto gender{ input("Enter Gender (Male, Female, Other): ", genderRegex, true) };
    if (gender != "#") setGender(stringToGender(gender));

    auto doJ{ input("Enter DOJ (dd-mm-yyyy): ", dateRegex,true) };
    if (doJ != "#") setDoj(doJ);

    auto mid{ input("Enter Manager Id: ",idRegex, true) };
    if (mid != "#") setManagerId(stoi(mid));

    auto did{ input("Enter Department Id: ", idRegex , true) };
    if (did != "#") setDepartmentId(stoi(did));

    salary.setID(getId());
  
    return salary.getUserInputForUpdate();
}

std::optional<Employee> Employee::getEmployeeById(int id) {
    auto dbI = DB::getDB();

    Employee employee;

    auto callback = [](void* data, int argc, char** argv, char** azColName) {
        Employee* employee = static_cast<Employee*>(data);

        employee->setId(std::stoi(argv[0]));
        employee->setFirstname(argv[1]);
        employee->setLastname(argv[2]);
        employee->setDob(argv[3]);
        employee->setMobile(argv[4]);
        employee->setEmail(argv[5]);
        employee->setAddress(argv[6]);
        employee->setGender(stringToGender(argv[7]));
        employee->setDoj(argv[8]);
        if (argv[9]) {
            employee->setManagerId(std::stoi(argv[9]));
        }
        else {
            employee->setManagerId(-1);
        }
       
        employee->setDepartmentId(std::stoi(argv[10]));

        return 0;
        };


    std::string selectQuery = "SELECT * FROM Employee WHERE id = " + std::to_string(id) + ";";
    dbI->executeSelectQuery(selectQuery.c_str(), callback, &employee, "Employee selected with ID " + std::to_string(id));

    if (employee.getId() == 0) {
        return std::nullopt;
    }
    auto salary1 = Salary::getSalaryByID(id);

        if(salary1) {
            employee.salary = std::move(*salary1);
        }
   
    return employee;
}

std::vector<Employee> Employee::getMultipleEmployee(const std::string& queryField, const std::string& queryValue) {
    auto dbI = DB::getDB();

    std::vector<Employee> vecOfEmp;

    std::string selectQuery;


    if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
        selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = " + queryValue + "; ";

    }
    else if (queryField == "" && queryValue == "") {
        selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id ;";
    }
    else {
        selectQuery = "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = '" + queryValue + "';";
    }


    auto callback = [](void* data, int argc, char** argv, char** azColName) {
        std::vector<Employee>* vecOfEmp = static_cast<std::vector<Employee>*>(data);

        Employee employee;

        employee.setId(std::stoi(argv[0]));
        employee.setFirstname(argv[1]);
        employee.setLastname(argv[2]);
        employee.setDob(argv[3]);
        employee.setMobile(argv[4]);
        employee.setEmail(argv[5]);
        employee.setAddress(argv[6]);
        employee.setGender(stringToGender(argv[7]));
        employee.setDoj(argv[8]);
        if (argv[9]) {
            employee.setManagerId(std::stoi(argv[9]));
        }
        else {
            employee.setManagerId(-1);
        }
        employee.setDepartmentId(std::stoi(argv[10]));
        employee.setSalary((Salary::getSalaryByID(std::stoi(argv[0])).value()));

        vecOfEmp->push_back(std::move(employee));
        return 0;
        };

    dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "Multiple Employee selected.");

    return vecOfEmp;
}

bool Employee::save() {
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
        "," +  std::to_string(department_id) + ");";

    if (!dbI->executeQuery(insertQuery.c_str(), "An Employee Inserted with ID: " + std::to_string(id))) {
        return false;
    }

    salary.save();

    return true;
}

bool Employee::deleteThis() {
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

bool Employee::update() {
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