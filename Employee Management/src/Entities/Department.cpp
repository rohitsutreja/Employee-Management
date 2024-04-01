#include "../../include/Entities/Department.h"


namespace Entity {

    std::optional<Department>  Department::getDepartmentById(int id) {
        auto dbI = DB::getDB();

        Department department;

        std::string selectQuery = "SELECT * FROM Department WHERE id = " + std::to_string(id) + " COLLATE NOCASE;";

        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            Department* dpt = static_cast<Department*>(data);

            dpt->setId(argv[0] ? std::stoi(argv[0]) : -1);
            dpt->setName(argv[1] ? argv[1] : "");
            dpt->setManagerId(argv[2] ? std::stoi(argv[2]) : -1);
            dpt->setDescription(argv[3] ? argv[3] : "");
            return 0;
            };

        try {
            dbI->executeSelectQuery(selectQuery.c_str(), callback, &department, "Department selected with ID " + std::to_string(id));
        }
        catch (...) {
            return std::nullopt;
        }

        if (department.getId() == 0) {
            return std::nullopt;
        }

        return department;
    }

    std::vector<Department>  Department::getMultipleDepartment(const std::string& queryField, const std::string& queryValue) {
        auto dbI = DB::getDB();

        std::vector<Department> listOfDepartment;

        std::string selectQuery;

        if (queryField == "id" || queryField == "Department.manager_id") {
            selectQuery = "SELECT Department.* FROM Department LEFT JOIN Employee ON Employee.id = Department.manager_id WHERE " + queryField + " = " + queryValue + " COLLATE NOCASE; ";

        }
        else if (queryField == "" && queryValue == "") {
            selectQuery = "SELECT Department.* FROM Department LEFT JOIN Employee ON Employee.id = Department.manager_id COLLATE NOCASE;";
        }
        else {
            selectQuery = "SELECT Department.* FROM Department LEFT JOIN Employee ON Employee.id = Department.manager_id WHERE " + queryField + " = '" + queryValue + "' COLLATE NOCASE;";
        }


        auto callback = [](void* data, int argc, char** argv, char** azColName) {
            std::vector<Department>* list = static_cast<std::vector<Department>*>(data);

            Department dpt;

            dpt.setId(argv[0] ? std::stoi(argv[0]) : -1);
            dpt.setName(argv[1] ? argv[1] : "");
            dpt.setManagerId(argv[2] ? std::stoi(argv[2]) : -1);
            dpt.setDescription(argv[3] ? argv[3] : "");

            list->push_back(std::move(dpt));

            return 0;
            };

        try {
            dbI->executeSelectQuery(selectQuery.c_str(), callback, &listOfDepartment, "Multiple Department selected.");
        }
        catch (...) {
            return {};
        }


        return listOfDepartment;

    }

    bool Department::save() const {
        auto dbI = DB::getDB();

        std::string  insertQuery = "INSERT INTO Department "
            "(id, name, manager_id, description) VALUES (";

        insertQuery += std::to_string(id) +
            ",'" + name +
            "'," + (manager_id == -1 ? "NULL" : std::to_string(manager_id)) +
            ",'" + description + "');";

        if (!dbI->executeQuery(insertQuery.c_str(), "A Departement Inserted with ID: " + std::to_string(id) + "\n")) { return false; }

        return true;
    }

    bool Department::update() const {
        auto dbI = DB::getDB();


        std::string updateQuery = "UPDATE Department SET ";
        updateQuery +=
            "name='" + name +
            "', manager_id=" + (manager_id == -1 ? "NULL" : std::to_string(manager_id)) +
            ", description='" + description +
            "' WHERE id = " + std::to_string(id) + ";";


        if (!dbI->executeQuery(updateQuery.c_str(), "Department Updated with ID: " + std::to_string(id) + ".")) return false;


        if (dbI->noOfRowChanged() == 0) {
            return false;
        }

        return true;
    }

    bool Department::deleteThis() const {
        auto dbI = DB::getDB();

        std::string deleteQuery = "DELETE FROM Department WHERE id = ";

        deleteQuery += std::to_string(id);

        if (!dbI->executeQuery(deleteQuery.c_str(), "Department Deleted with ID: " + std::to_string(id) + ".")) { return false; }

        if (dbI->noOfRowChanged() == 0) return false;

        return true;
    }

    bool Department::getUserInput() noexcept {
        try {
            std::cout << "- Insert Department Details\n\n";
            std::cout << "- Enter ':q' at any point to cancel insertion\n\n";

            setId(stoi(inputWithQuit("Enter Department ID: ", idRegex)));
            setName(inputWithQuit("Enter Department Name: ", nonEmptyRegex));

            auto mId = inputWithQuit("Enter Department Manager Id ('#' to skip): ", idRegex, true);
            setManagerId(mId == "#" ? -1 : stoi(mId));

            setDescription(inputWithQuit("Enter Description: ", nonEmptyRegex));

            return true;

        }
        catch (...) {
            return false;
        }

    }

    bool Department::getUserInputForUpdate() noexcept {
        try {
            std::cout << "- Update Details of Department with id: " << id << "\n\n";
            std::cout << "- Enter ':q' at any point to cancel updation\n\n";
            std::cout << "- Enter '#' to keep the value as it is.\n\n";

            auto name{ inputWithQuit("Enter Department Name: ", nonEmptyRegex , true) };
            if ((name != "#")) { setName(name); }

            auto mid{ inputWithQuit("Enter Manager ID: ", idRegex , true) };
            if ((mid != "#")) { setManagerId(stoi(mid)); }

            auto desc{ inputWithQuit("Enter brief Description: ", nonEmptyRegex , true) };
            if ((desc != "#")) { setDescription(desc); }

            return true;
        }
        catch (...) {
            return false;
        }
    }

    void  Department::display() const {

        auto dbI = DB::getDB();

        std::string managerName = "-";

        if (manager_id != -1) {
            std::string selectQuery = "SELECT id, firstname, lastname FROM EMPLOYEE WHERE id = " + std::to_string(manager_id) + ";";
            dbI->executeSelectQuery(selectQuery.c_str(), [](void* data, int argc, char** argv, char** aZcolname) {
                auto managerName = static_cast<std::string*>(data);

                *managerName = argv[1] ? argv[1] : "";
                *managerName += " ";
                *managerName += argv[2] ? argv[2] : "";

                *managerName += " (ID - ";
                *managerName += argv[0] ? argv[0] : "";
                *managerName += ")";

                return 0;
                }, &managerName, "Employee name selected to display department");
        }

        std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
        std::cout << "|\033[32m ID\033[0m                         | " << std::setw(48) << std::left << id << " |" << std::endl;
        std::cout << "| Department Name            | " << std::setw(48) << std::left << name << " |" << std::endl;
        std::cout << "| Manager Name               | " << std::setw(48) << std::left << managerName << " |" << std::endl;
        std::cout << "| Description                | " << std::setw(48) << std::left << description << " |" << std::endl;
        std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
    }

}
