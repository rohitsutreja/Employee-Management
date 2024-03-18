#include "../include/Department.h"

void  Department::display() const {
    auto dbI = DB::getDB();

    std::string managerName = "-";
    std::string selectQuery = "SELECT id, firstname, lastname FROM EMPLOYEE WHERE id = " + std::to_string(manager_id) + ";";
    dbI->executeSelectQuery(selectQuery.c_str(), [](void* data, int argc, char** argv, char** aZcolname) {
        auto m = static_cast<std::string*>(data);

        *m = argv[1];
        *m += " ";
        *m += argv[2];

        *m += " (ID - ";
        *m += argv[0];
        *m += ")";

        return 0;
        }, &managerName, "Employee name selected to display department");


    if (manager_id == -1) {
        managerName = "-";
    }

    std::cout << "+------------------+----------------------------------------+" << std::endl;
    std::cout << "|\033[32m ID\033[0m               | " << std::setw(38) << std::left << id << " |" << std::endl;
    std::cout << "| Department Name  | " << std::setw(38) << std::left << name << " |" << std::endl;
    std::cout << "| Manager Name     | " << std::setw(38) << std::left << managerName << " |" << std::endl;
    std::cout << "| Description      | " << std::setw(38) << std::left << description << " |" << std::endl;
    std::cout << "+------------------+----------------------------------------+" << std::endl;
}

void  Department::getUserInput() {
    setId(stoi(input("Enter Department ID: ", idRegex)));
    setName(input("Enter Department Name: ", nonEmptyRegex));
    auto mId = input("Enter Department Manager Id ('#' to skip): ", idRegex, true);
    if (mId == "#") {
        setManagerId(-1);
    }
    else {
        setManagerId(stoi(mId));
    }

    setDescription(input("Enter Description: ", nonEmptyRegex));
}

void  Department::getUserInputForUpdate() {
    std::cout << "Update Department with id: " << id;

    std::cout << "\n\nPlease enter the updated values or '#' to keep the value as it is\n\n";

    auto name{ input("Enter Department Name: ", nonEmptyRegex , true) };
    if ((name != "#")) { setName(name); }

    auto mid{ input("Enter Manager ID: ", idRegex , true) };
    if ((mid != "#")) { setManagerId(stoi(mid)); }

    auto desc{ input("Enter brief Description: ", nonEmptyRegex , true) };
    if ((desc != "#")) { setDescription(desc); }
}

bool  Department::save() {
    auto dbI = DB::getDB();

    std::string  insertQuery = "INSERT INTO Department "
        "(id, name, manager_id, description) VALUES (";

    insertQuery += std::to_string(id) +
        ",'" + name +
        "'," + std::to_string(manager_id) +
        ",'" + description + "');";

    if (!dbI->executeQuery(insertQuery.c_str(), "A Departement Inserted with ID: " + std::to_string(id) + "\n")) { return false; }

    return true;
}

std::optional<Department>  Department::getDepartmentById(int id) {
    auto dbI = DB::getDB();


    Department dpt;

    std::string selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(id) + ";";

    auto callback = [](void* data, int argc, char** argv, char** azColName) {
        Department* dpt = static_cast<Department*>(data);

        dpt->setId(std::stoi(argv[0]));
        dpt->setName(argv[1]);
        dpt->setManagerId(std::stoi(argv[2]));
        dpt->setDescription(argv[3]);
        return 0;
        };

    dbI->executeSelectQuery(selectQuery.c_str(), callback, &dpt, "Department selected with ID " + std::to_string(id));

    if (dpt.getId() == 0) {
        return {};
    }
    return dpt;
}

std::vector<Department>  Department::getMultipleDepartment(const std::string& queryField, const std::string& queryValue) {
    auto dbI = DB::getDB();


    std::vector<Department> vecOfDep;

    std::string selectQuery;

    if (queryField == "id" || queryField == "manager_id") {
        selectQuery = "SELECT Department.* FROM Department LEFT  JOIN Employee ON Employee.id = Department.manager_id WHERE " + queryField + " = " + queryValue + "; ";

    }
    else if (queryField == "" && queryValue == "") {
        selectQuery = "SELECT Department.* FROM Department LEFT JOIN Employee ON Employee.id = Department.manager_id ;";
    }
    else {
        selectQuery = "SELECT Department.* FROM Department LEFT JOIN Employee ON Employee.id = Department.manager_id WHERE " + queryField + " = '" + queryValue + "';";
    }


    auto callback = [](void* data, int argc, char** argv, char** azColName) {
        std::vector<Department>* vecOfDep = static_cast<std::vector<Department>*>(data);

        Department dpt;

        dpt.setId(std::stoi(argv[0]));
        dpt.setName(argv[1]);
        dpt.setManagerId(std::stoi(argv[2]));
        dpt.setDescription(argv[3]);

        vecOfDep->push_back(std::move(dpt));

        return 0;
        };

    dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfDep, "Multiple Department selected.");

    return vecOfDep;

}

bool Department::deleteThis() {
    auto dbI = DB::getDB();

    std::string deleteQuery = "DELETE FROM Department WHERE id = ";
    deleteQuery += std::to_string(id);

    if (!dbI->executeQuery(deleteQuery.c_str(), "Department Deleted with ID: " + std::to_string(id) + ".")) { return false; }

    return true;
}

bool  Department::update() {
    auto dbI = DB::getDB();


    std::string updateQuery = "UPDATE Department SET ";
    updateQuery +=
        "name='" + name +
        "', manager_id=" + std::to_string(manager_id) +
        ", description='" + description +
        "' WHERE id = " + std::to_string(id) + ";";


    if (!dbI->executeQuery(updateQuery.c_str(), "Department Updated with ID: " + std::to_string(id) + ".")) return false;

    return true;
}

