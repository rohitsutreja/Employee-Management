
#include "include/Util.h"
#include "include/Entities/Employee.h"
#include "include/Entities/Manager.h"

void insertEmployee() {
	clearDisplay();

	Employee employee;

	if (!employee.getUserInput()) {
		clearDisplay();
		std::cout << "Insertion cancelled\n";
		return;
	};

	if (auto duplicateEmployee = Employee::getEmployeeById(employee.getId()); duplicateEmployee) {
		std::cout << "This employee id already exists, Please try again with another id.\n";
		return;
	}

	if (auto department = Department::getDepartmentById(employee.getDepartmentId()); !department) {
		std::cout << "This department does not exist, Please try again with valid department id\n";
		return;
	}
	if (auto manager = Manager::getManagerById(employee.getManagerId());  employee.getManagerId() != -1 && !manager) {
		std::cout << "This manager does not exist, Please try again with valid manager id or without manager\n";
		return;
	}

	if (employee.save()) {
		std::cout << "Insertion Successfull.\n";
	}
	else {
		std::cout << "Insertion Failed\n";
	};
}
void updateEmployee() {

	auto id = stoi(input("Please enter id of the employee: ", idRegex));
	auto employee = Employee::getEmployeeById(id);

	clearDisplay();

	if (employee) {
		clearDisplay();

		auto oldMid = employee->getManagerId();
		auto oldDid = employee->getDepartmentId();

		if (!employee->getUserInputForUpdate()) {
			clearDisplay();
			std::cout << "Updation cancelled\n";
			return;
		};

		auto newMid = employee->getManagerId();
		auto newDid = employee->getDepartmentId();

		if (oldDid != newDid) {
			if (auto department = Department::getDepartmentById(employee->getDepartmentId()); !department) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
				return;
			}
		}
		if (oldMid != newMid) {
			if (auto manager = Manager::getManagerById(employee->getManagerId()); !manager) {
				std::cout << "This manager does not exist, Please try again with valid manager id\n";
				return;
			}
		}

		if (employee->update()) {
			std::cout << "Updation Successfull.\n";
		}
		else {
			std::cout << "Updation Failed.\n";
		}
	}
	else {
		std::cout << "No employee exist with id: " << id << "\n";
	}
};
void deleteEmployee() {
	int id = stoi(input("Please enter Id of the employee: ", idRegex));

	auto managerOfEmployees = Employee::getMultipleEmployee("Employee.manager_id", std::to_string(id));
	auto managerOfDepartments = Department::getMultipleDepartment("Department.manager_id", std::to_string(id));

	if ((managerOfEmployees.size() != 0) || (managerOfDepartments.size() != 0)) {
		std::cout << "This employee is manager of [" << managerOfEmployees.size() << "] employees and [" << managerOfDepartments.size() << "] departments\n\n";
		std::cout << "If you delete this employee, they will be manager less.\n\n";
		auto ip = input("Do you still want to delete it? ( Y / N ): ", std::regex{ "^[YNyn]$" });
		if (ip == "N" || ip == "n") {
			std::cout << "\nDeletion cancelled\n";
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

	auto employee = Employee::getEmployeeById(id);
	if (employee) {
		if (employee->deleteThis()) {
			std::cout << "Employee with id: " << id << " deleted successfully.\n";
		}
		else {
			std::cout << "Employee couldn't be deleted\n";
		}

	}
	else {
		std::cout << "No Employee exist with id: " << id << "\n";
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
		queryField = input("Please enter id: ", idRegex);
		auto employee = Employee::getEmployeeById(stoi(queryField));

		clearDisplay();
		if (employee) {
			std::cout << "Employee with id: " << queryField << '\n';
			employee->display();
		}
		else {
			std::cout << "No Employee exist with id: " << queryField << "\n";
		}
		break;
	}
	case 2: {
		queryField = input("Please enter fisrt name: ");
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
