#include "include/Util.h"
#include "include/Entities/Department.h"
#include "include/Entities/Manager.h"

using Entity::Department;
using Entity::Employee;
using Entity::Manager;

namespace Controller {
	void insertDepartment() {
		clearDisplay();

		Department department;

		if (!department.populateForInsertion()) {
			clearDisplay();
			std::cout << getInCyan("- Insertion cancelled.\n");
			return;
		}

		clearDisplay();

		if (auto duplicateDepartment = Department::getDepartmentById(department.getId()); duplicateDepartment) {
			std::cout << getInCyan("- This department id already exists") << ", Please try again with another id.\n";
			return;
		}

		if (auto manager = Manager::getManagerById(department.getManagerId()); !manager) {
			std::cout << getInCyan("- No manager exist with this id") << ", Please retry with valid manager id or skip it.\n";
			return;
		}

		if (department.save()) {
			std::cout << getInGreen("- Insertion successful.") << '\n';
		}
		else {
			std::cout << getInRed("- Insertion failed.") << '\n';
		};

	};
	void updateDepartment() {
		auto id = input("- Please enter id of the department (Enter '#' to cancel updation): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Updation cancelled.\n");
			return;
		}
		
		auto department = Department::getDepartmentById(stoi(id));

		clearDisplay();
		if (department) {
			auto oldMid = department->getManagerId();

			if (!department->populateForUpdation()) {
				clearDisplay();
				std::cout << getInCyan("- Updation cancelled.\n");
				return;
			}

			auto newMid = department->getManagerId();

			clearDisplay();
			if (oldMid != newMid) {
				if (auto manager = Manager::getManagerById(newMid); !manager) {
					std::cout << getInCyan("- No manager exist with this id") <<", Please retry with valid manager id.\n";
					return;
				}
			}
			if (department->update()) {
				std::cout << getInGreen("- Updation successful.") << '\n';
			}
			else {
				std::cout << getInRed("- Updation failed.") << '\n';
			}
		}
		else {
			std::cout << getInCyan("- No department exist with id : ") << id << "\n";
		}

	};
	void deleteDepartment() {

		auto id = input("- Please enter id of the department (Enter '#' to cancel deletion): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Deletion cancelled.\n");
			return;
		}
		
		auto department = Department::getDepartmentById(stoi(id));


		clearDisplay();
		if (department) {
			auto employyesInDepartment = Employee::getMultipleEmployee("department_id", std::to_string(department->getId()));
			if (employyesInDepartment.size() != 0) {
				std::cout << "- There are total [" << employyesInDepartment.size() << "] employees in this department.\n\n";
				std::cout << "- If you delete this department, they will be deleted too.\n\n";
				auto ip = input("- Do you still want to delete it? ( Y / N ): ", yesNoRegex);

				clearDisplay();
				if (ip == "N" || ip == "n") {
					std::cout << getInCyan("- Deletion cancelled.\n");
					return;
				}
				for (auto e : employyesInDepartment) {
					e.deleteThis();
				}
				if (department->deleteThis()) {
					std::cout << getInGreen("- Deletion successful.") << '\n';
				}
				else {
					std::cout << getInRed("- Deletion failed.") << '\n';
				}

			}
		}
		else {
			std::cout << getInCyan("- No department exist with id : ") << id << "\n";
		}
	}
	void viewDepartments() {
		std::string queryField;
		auto choice{ 0 };

		std::cout << "1. View by ID\n";
		std::cout << "2. View by name\n";
		std::cout << "3. View by manager ID\n";
		std::cout << "4. View All Departments\n\n";

		choice = stoi(input("Please Select an Option (1-4): ", std::regex("^[1-4]$")));

		clearDisplay();
		switch (choice) {
		case 1: {
			queryField = input("Please enter id: ", idRegex);
			auto department = Department::getDepartmentById(stoi(queryField));

			clearDisplay();
			if (department) {
				std::cout << "Department with id: " << getInGreen(queryField) << "\n\n";
				department->display();
				if (department->getDescription().size() >= 48) {
					auto choice = input("\n- Do you want to see full description of the department? (Y/N): ", yesNoRegex);
					if (choice == "Y" || choice == "y") {
						std::cout << '\n' << "- Description: " << department->getDescription() << '\n';
						
					}
				}
			}
			else {
				std::cout << getInCyan("- No department exists with id: ") + queryField + ".\n";
			}
			return;
		}
		case 2: {
			queryField = input("Please enter name: ");
			auto departmentVector = Department::getMultipleDepartment("name", queryField);
			displayVector(departmentVector);
			break;
		}
		case 3: {
			queryField = input("Please enter manager ID: ");
			auto departmentVector = Department::getMultipleDepartment("Department.manager_id", queryField);
			displayVector(departmentVector);
			break;
		}
		case 4: {
			auto departmentVector = Department::getMultipleDepartment();
			displayVector(departmentVector);
			break;
		}
		}
	};
}