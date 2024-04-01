#include "include/Entities/Manager.h"
#include "include/Util.h"

using Entity::Employee;
using Entity::Manager;
using Entity::Department;


namespace Controller {
	void insertManager() {

		clearDisplay();

		Manager manager;

		if (!manager.populateForInsertion()) {
			clearDisplay();
			std::cout << getInCyan("- Insertion cancelled.\n");
			return;
		}
		if (auto duplicateManager = Employee::getEmployeeById(manager.getId()); duplicateManager) {
			std::cout << getInCyan("- This employee id already exists") <<", Please try again with another id.\n";
			return;
		}

		if (auto department = Department::getDepartmentById(manager.getDepartmentId());  !department) {
			std::cout << getInCyan("- This department does not exist") << ", Please try again with valid department id.\n";
			return;
		}
		if (auto managerOfManager = Manager::getManagerById(manager.getManagerId());  manager.getManagerId() != -1 && !managerOfManager) {
			std::cout << getInCyan("- This manager of manager does not exist") <<", Please try again with valid manager id or without manager.\n";
			return;
		}

		if (manager.save()) {
			std::cout << getInGreen("- Insertion successful.") << '\n';
		}
		else {
			std::cout << getInRed("- Insertion failed.") << '\n';
		};
	};
	void updateManager() {
		auto id = input("- Please enter id of the manager (Enter '#' to cancel updation): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Updation cancelled.\n");
			return;
		}
	
		auto manager = Manager::getManagerById(stoi(id));

		clearDisplay();
		if (manager) {
			auto oldMid = manager->getManagerId();
			auto oldDid = manager->getDepartmentId();

			if (!manager->populateForUpdation()) {
				clearDisplay();
				std::cout << getInCyan("- Updation cancelled.\n");
				return;
			}

			clearDisplay();
			auto newMid = manager->getManagerId();
			auto newDid = manager->getDepartmentId();

			if (oldDid != newDid) {
				if (auto department = Department::getDepartmentById(manager->getDepartmentId()); !department) {
					std::cout << getInCyan("- This department does not exist")<<", Please try again with valid department id.\n";
					return;
				}
			}

			if (oldMid != newMid) {

				if (auto managerOfManager = Manager::getManagerById(manager->getManagerId()); !managerOfManager) {
					std::cout << getInCyan("- This manager does not exist")<<", Please try again with valid manager id.\n";
					return;
				}
			}

			if (manager->update()) {
				std::cout << getInGreen("- Updation successful.") << '\n';
			}
			else {
				std::cout << getInRed("- Updation failed.") << '\n';
			}
		}
		else {
			std::cout << getInCyan("- No manager exist with id: ") << id << "\n";
		}
	};
	void deleteManager() {
		auto id = input("- Please enter id of the manager (Enter '#' to cancel deletion): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Deletion cancelled.\n");
			return;
		}
		

		clearDisplay();

		auto managerOfEmployees = Employee::getMultipleEmployee("Employee.manager_id", id);
		auto managerOfDepartments = Department::getMultipleDepartment("Department.manager_id",id);

		if ((managerOfEmployees.size() != 0) || (managerOfDepartments.size() != 0)) {
			std::cout << "This employee is manager of [" << managerOfEmployees.size() << "] employees and [" << managerOfDepartments.size() << "] departments\n\n";
			std::cout << "If you delete this employee, they will be manager less.\n\n";
			auto ip = input("Do you still want to delete it? ( Y / N ): ", std::regex{ "^[YNyn]$" });

			clearDisplay();
			if (ip == "N" || ip == "n") {
				std::cout << getInCyan("- Deletion cancelled.\n");
				return;
			}
			else {
				for (auto e : managerOfEmployees) {
					e.setManagerId(-1);
					e.update();
				}
				for (auto e : managerOfDepartments) {
					e.setManagerId(-1);
					e.update();
				}
			}
		}

		auto manager = Manager::getManagerById(stoi(id));
		if (manager) {
			if (manager->deleteThis()) {
				std::cout << getInGreen("- Deletion successful.") << '\n';
			}
			else {
				std::cout << getInGreen("- Deletion failed.") << '\n';
			}

		}
		else {
			std::cout << getInCyan("- No manager exist with id: ") << id << "\n";
		}

	};
	void viewManagers() {
		std::string queryField;
		auto choice{ 0 };

		std::cout << "1. View by ID\n";
		std::cout << "2. View by first name\n";
		std::cout << "3. View by last name\n";
		std::cout << "4. View by Department\n";
		std::cout << "5. View All Managers\n\n";

		choice = stoi(input("Please Select an Option: ", std::regex("^[1-5]$")));

		clearDisplay();
		switch (choice) {
		case 1: {

			queryField = input("- Please enter ID: ", idRegex);
			auto manager = Manager::getManagerById(stoi(queryField));

			clearDisplay();
			if (manager) {
				std::cout << "- Manager with id: " << getInGreen(queryField) << '\n';
				manager->display();
			}
			else {
				std::cout << getInCyan("- No manager exist with id: ") << queryField << "\n";
			}
			return;

		}
		case 2: {
			queryField = input("- Please enter fisrt name: ");
			auto managersVector = Manager::getMultipleManagers("firstname", queryField);
			displayVector(managersVector);
			break;
		}
		case 3: {
			queryField = input("- Please enter last name: ");
			auto managersVector = Manager::getMultipleManagers("lastname", queryField);
			displayVector(managersVector);
			break;
		}
		case 4: {
			queryField = input("- Please enter department name: ");
			auto managersVector = Manager::getMultipleManagers("department.name", queryField);
			displayVector(managersVector);
			break;
		}
		case 5: {
			auto managersVector = Manager::getMultipleManagers();
			displayVector(managersVector);
			break;
		}
		}
	};
}