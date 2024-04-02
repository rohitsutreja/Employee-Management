#include "../../include/Util.h"
#include "../../include/Entities/Employee.h"
#include "../../include/Entities/Manager.h"

using Entity::Department;
using Entity::Employee;
using Entity::Manager;
using Entity::Salary;

namespace Controller {
	void insertEmployee() {
		clearDisplay();

		Employee employee;

		if (!employee.populateForInsertion()) {
			clearDisplay();
			std::cout << getInCyan("- Insertion cancelled.\n");
			return;
		};

		clearDisplay();
		if (auto duplicateEmployee = Employee::getEmployeeById(employee.getId()); duplicateEmployee) {
			std::cout << "- This employee id " << getInCyan("already exist") << ", Please try again with another id.\n";
			return;
		}


		if (auto department = Department::getDepartmentById(employee.getDepartmentId()); !department) {
			std::cout << "- This department " <<  getInCyan("does not exist") << ", Please try again with valid department id.\n";
			return;
		}

		if (auto manager = Manager::getManagerById(employee.getManagerId());  employee.getManagerId() != -1 && !manager) {
			std::cout << "- This manager "<< getInCyan("does not exist") << ", Please try again with valid manager id or without manager.\n";
			return;
		}

		

		if (employee.save()) {
			std::cout << getInGreen("- Insertion successful.") << '\n';
		}
		else {
			std::cout << getInRed("- Insertion failed.") << '\n';
		};
	}
	void updateEmployee() {

		auto id = input("- Please enter id of the employee (Enter '#' to cancel updation): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Updation cancelled.\n");
			return;
		}

		auto employee = Employee::getEmployeeById(stoi(id));

		clearDisplay();

		if (employee) {
			clearDisplay();

			auto oldMid = employee->getManagerId();
			auto oldDid = employee->getDepartmentId();

			if (!employee->populateForUpdation()) {
				clearDisplay();
				std::cout << getInCyan("- Updation cancelled.\n");
				return;
			};

			auto newMid = employee->getManagerId();
			auto newDid = employee->getDepartmentId();

			clearDisplay();
			if (oldDid != newDid) {
				if (auto department = Department::getDepartmentById(employee->getDepartmentId()); !department) {
					std::cout << "- This department "<< getInCyan("does not exist") << ", Please try again with valid department id.\n";
					return;
				}
			}
			if (oldMid != newMid) {
				if (auto manager = Manager::getManagerById(employee->getManagerId()); !manager) {
					std::cout << "- This manager " << getInCyan("does not exist") << ", Please try again with valid manager id.\n";
					return;
				}
			}

			if (employee->update()) {
				std::cout << getInGreen("- Updation Successfull.") << '\n';
			}
			else {
				std::cout << getInRed("- Updation Failed.") << '\n';
			}
		}
		else {
			std::cout << getInCyan("- No employee exist with id: ") << id << "\n";
		}
	};
	void deleteEmployee() {
		auto id = input("- Please enter id of the employee (Enter '#' to cancel deletion): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Deletion cancelled.\n");
			return;
		}

		auto managerOfEmployees = Employee::getMultipleEmployee("Employee.manager_id", id);
		auto managerOfDepartments = Department::getMultipleDepartment("Department.manager_id", id);

		clearDisplay();
		if ((managerOfEmployees.size() != 0) || (managerOfDepartments.size() != 0)) {
			std::cout << "- This employee is manager of [" << managerOfEmployees.size() << "] employees and [" << managerOfDepartments.size() << "] departments\n\n";
			std::cout << "- If you delete this employee, they will be manager less.\n\n";
			auto ip = input("- Do you still want to delete it? ( Y / N ): ", std::regex{ "^[YNyn]$" });

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

		auto employee = Employee::getEmployeeById(stoi(id));

		if (employee) {
			if (employee->deleteThis()) {
				std::cout << getInGreen("- Deletion successful.") << '\n';
			}
			else {
				std::cout << getInRed("- Deletion failed.") << '\n';
			}

		}
		else {
			std::cout << getInCyan("- No Employee exist with id: ") << id << "\n";
		}
	};
	void viewEmployees() {
		std::string queryField;
		auto choice{ 0 };

		std::cout << "0. Go Back\n";
		std::cout << "1. View by ID\n";
		std::cout << "2. View by first name\n";
		std::cout << "3. View by last name\n";
		std::cout << "4. View by Department\n";
		std::cout << "5. View All Employee\n\n";

		choice = stoi(input("Please Select an Option: ", std::regex("^[0-5]$")));

		if (choice == 0) {
			return;
		}

		clearDisplay();
		switch (choice) {
		case 1: {
			queryField = input("- Please enter id: ", idRegex);
			auto employee = Employee::getEmployeeById(stoi(queryField));

			clearDisplay();
			if (employee) {
				std::cout << "- Employee with id: " << getInGreen(queryField) << "\n\n";
				employee->display();
			}
			else {
				std::cout << getInCyan("- No Employee exist with id: ") << queryField << "\n";
			}
			break;
		}
		case 2: {
			queryField = input("Please enter first name: ");
			auto employeesVector = Employee::getMultipleEmployee("firstname", queryField);
			displayVector(employeesVector);
			break;
		}
		case 3: {
			queryField = input("Please enter last name: ");
			auto employeesVector = Employee::getMultipleEmployee("lastname", queryField);
			displayVector(employeesVector);
			break;
		}
		case 4: {
			queryField = input("Please enter department name: ");
			auto employeesVector = Employee::getMultipleEmployee("department.name", queryField);
			displayVector(employeesVector);
			break;
		}
		case 5: {
			auto employeesVector = Employee::getMultipleEmployee();
			displayVector(employeesVector);
			break;
		}
		}
	};
}