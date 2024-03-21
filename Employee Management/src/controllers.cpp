#include <iostream>
#include "../sqlite/sqlite3.h"
#include "../include/Entities/Employee.h"
#include "../include/DB.h"
#include "../include/Regex.h"
#include "../include/Entities/Department.h"
#include "../include/Entities/Engineer.h"
#include "../include/Entities/Manager.h"
#include "../include/controllers.h"


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

	auto managerOfEmployees = Employee::getMultipleEmployee("Employee.manager_id",std::to_string(id));
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

void insertEngineer() {
	clearDisplay();

	Engineer engineer;
	if (!engineer.getUserInput())
	{
		clearDisplay();
		std::cout << "Insertion cancelled\n";
		return;
	}
	if (auto duplicateEngineer = Employee::getEmployeeById(engineer.getId()); duplicateEngineer) {
		std::cout << "This employee id already exists, Please try again with another id.\n";
		return;
	}
	if (auto department = Department::getDepartmentById(engineer.getDepartmentId()); !department) {
		std::cout << "This department does not exist, Please try again with valid department id\n";
	}
	else {
		if (auto manager = Manager::getManagerById(engineer.getManagerId()); engineer.getManagerId() != -1 && !manager) {
			std::cout << "This manager does not exist, Please try again with valid manager id or without manager\n";
		}
		else {
			if (engineer.save()) {
				std::cout << "Insertion Successfull.\n";
			}
			else {
				std::cout << "Insertion Failed.\n";
			};
		}

	}
};
void updateEngineer() {
	auto id = stoi(input("Please enter id of the engineer: ", idRegex));
	auto engineer = Engineer::getEngineerById(id);

	if (engineer) {
		auto oldMid = engineer->getManagerId();
		auto oldDid = engineer->getDepartmentId();

		if (!engineer->getUserInputForUpdate()) {
			clearDisplay();
			std::cout << "Updation cancelled\n";
			return;
		}

		clearDisplay();

		auto newMid = engineer->getManagerId();
		auto newDid = engineer->getDepartmentId();

		if (oldDid != newDid) {
			if (auto department = Department::getDepartmentById(newDid); !department) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
				return;
			}
		}

		if (oldMid != newMid) {
			if (auto manager = Manager::getManagerById(newMid); !manager) {
				std::cout << "This manager does not exist, Please try again with valid manager id\n";
				return;
			}
		}

		if (engineer->update()) {
			std::cout << "Updation Successfull.\n";
		}
		else {
			std::cout << "Updation Failed.\n";
		}
	}
	else {
		std::cout << "No engineer exist with id: " << id << "\n";
	}
};
void deleteEngineer() {
	int id = stoi(input("Please enter id of the engineer: ", idRegex));
	auto engineer = Engineer::getEngineerById(id);

	clearDisplay();
	if (engineer) {
		if (engineer->deleteThis()) {
			std::cout << "Deletion Successfull.\n";
		}
		else {
			std::cout << "Deletion Failed.\n";
		}

	}
	else {
		std::cout << "No engineer exist with id: " << id << "\n";
	}
};
void viewEngineers() {
	std::string queryField;
	auto choice{ 0 };

	std::cout << "1. View by ID\n";
	std::cout << "2. View by first name\n";
	std::cout << "3. View by last name\n";
	std::cout << "4. View by Department\n";
	std::cout << "5. View All Engineers\n";
	std::cout << "6. View by Programming Language\n";

	choice = stoi(input("Please Select an Option: ", std::regex("^[1-6]$")));

	clearDisplay();
	switch (choice) {
	case 1: {

		queryField = input("Please enter id: ", idRegex);
		auto engineer = Engineer::getEngineerById(stoi(queryField));

		clearDisplay();
		if (engineer) {
			std::cout << "Engineer with id: " << queryField << '\n';
			engineer->display();
		}
		else {
			std::cout << "No engineer exist with id: " << queryField << "\n";
		}

		return;
	}
	case 2: {
		queryField = input("Please enter fisrt name: ");
		auto engineersVector = Engineer::getMultipleEngineers("firstname", queryField);
		displayVector(engineersVector);
		break;
	}
	case 3: {
		queryField = input("Please enter last name: ");
		auto engineersVector = Engineer::getMultipleEngineers("lastname", queryField);
		displayVector(engineersVector);
		break;
	}
	case 4: {
		queryField = input("Please enter department name: ");
		auto engineersVector = Engineer::getMultipleEngineers("department.name", queryField);
		displayVector(engineersVector);
		break;
	}
	case 5: {
		auto engineersVector = Engineer::getMultipleEngineers();
		displayVector(engineersVector);
		break;
	}
	case 6: {
		queryField = input("Please enter programming language: ");
		auto engineersVector = Engineer::getMultipleEngineers("programming_language", queryField);
		displayVector(engineersVector);
		break;
	}
	}
};

void insertManager() {

	clearDisplay();

	Manager manager;

	if (!manager.getUserInput()) {
		clearDisplay();
		std::cout << "Insertion cancelled\n";
		return;
	}
	if (auto duplicateManager = Employee::getEmployeeById(manager.getId()); duplicateManager) {
		std::cout << "This employee id already exists, Please try again with another id.\n";
		return;
	}

	if (auto department = Department::getDepartmentById(manager.getDepartmentId());  !department) {
		std::cout << "This department does not exist, Please try again with valid department id\n";
	}
	else {
		if (auto managerOfManager = Manager::getManagerById(manager.getManagerId());  manager.getManagerId() != -1 && !managerOfManager) {
			std::cout << "This manager of manager does not exist, Please try again with valid manager id or without manager\n";
		}
		else {
			if (manager.save()) {
				std::cout << "Insertion Successfull.\n";
			}
			else {
				std::cout << "Insertion Failed.\n";
			};
		}

	}
};
void updateManager() {
	auto id = stoi(input("Please enter Id of the Manager: ", idRegex));
	auto manager = Manager::getManagerById(id);

	clearDisplay();
	if (manager) {
		auto oldMid = manager->getManagerId();
		auto oldDid = manager->getDepartmentId();

		if (!manager->getUserInputForUpdate()) {
			clearDisplay();
			std::cout << "Updation cancelled\n";
			return;
		}

		clearDisplay();
		auto newMid = manager->getManagerId();
		auto newDid = manager->getDepartmentId();

		if (oldDid != newDid) {
			if (auto department = Department::getDepartmentById(manager->getDepartmentId()); !department) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
				return;
			}
		}

		if (oldMid != newMid) {
		
			if (auto managerOfManager = Manager::getManagerById(manager->getManagerId()); !managerOfManager) {
				std::cout << "This manager does not exist, Please try again with valid manager id\n";
				return;
			}
		}

		if (manager->update()) {
			std::cout << "Updation Successfull.\n";
		}
		else {
			std::cout << "Updation Failed.\n";
		}
	}
	else {
		std::cout << "No manager exist with id: " << id << "\n";
	}
};
void deleteManager() {
	int id = stoi(input("Please enter Id of the Manager: ", idRegex));

	clearDisplay();

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

	auto manager = Manager::getManagerById(id);
	clearDisplay();
	if (manager) {
		if (manager->deleteThis()) {
			std::cout << "\nDeletion Successfull.\n";
		}
		else {
			std::cout << "\nDeletion Failed.\n";
		}

	}
	else {
		std::cout << "No manager exist with id: " << id << "\n";
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

		queryField = input("Please enter ID: ", idRegex);
		auto manager = Manager::getManagerById(stoi(queryField));

		clearDisplay();
		if (manager) {
			std::cout << "Manager with id: " << queryField << '\n';
			manager->display();
		}
		else {
			std::cout << "No manager exist with id: " << queryField << "\n";
		}
		return;

	}
	case 2: {
		queryField = input("Please enter fisrt name: ");
		auto managersVector = Manager::getMultipleManagers("firstname", queryField);
		displayVector(managersVector);
		break;
	}
	case 3: {
		queryField = input("Please enter last name: ");
		auto managersVector = Manager::getMultipleManagers("lastname", queryField);
		displayVector(managersVector);
		break;
	}
	case 4: {
		queryField = input("Please enter department name: ");
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

void insertDepartment() {
	clearDisplay();

	Department department;

	if (!department.getUserInput()) {
		clearDisplay();
		std::cout << "Insertion cancelled\n";
		return;
	}


	if (auto duplicateDepartment = Department::getDepartmentById(department.getId()); duplicateDepartment) {
		std::cout << "This employee id already exists, Please try again with another id.\n";
		return;
	}

	if (department.save()) {
		std::cout << "Insertion Successfull.\n";
	}
	else {
		std::cout << "Insertion Failed.\n";
	};

};
void updateDepartment() {
	int id = stoi(input("Please enter Id of the Department: ", idRegex));
	auto department = Department::getDepartmentById(id);

	clearDisplay();
	if (department) {
		auto oldMid = department->getManagerId();

		if (!department->getUserInputForUpdate()) {
			clearDisplay();
			std::cout << "Updation cancelled\n";
			return;
		}

		auto newMid = department->getManagerId();

		clearDisplay();
		if (oldMid != newMid) {
			if (auto manager = Manager::getManagerById(newMid); !manager) {
				std::cout << "No Manager exists with this id, Please retry with valid manager id\n";
				return;
			}
		}
		if (department->update()) {
			std::cout << "Updation Successfull.\n";
		}
		else {
			std::cout << "Updation Failed.\n";
		}
	}
	else {
		std::cout << "No department exist with id: " << id << "\n";
	}

};
void deleteDepartment() {
	int id = stoi(input("Please enter Id of the Department: ", idRegex));
	auto department = Department::getDepartmentById(id);


	clearDisplay();
	if (department) {
		auto employyesInDepartment = Employee::getMultipleEmployee("department_id", std::to_string(department->getId()));
		if (employyesInDepartment.size() != 0) {
			std::cout << "There are total [" << employyesInDepartment.size() << "] employees in this department.\n\n";
			std::cout << "If you delete this department, they will be deleted too.\n\n";
			auto ip = input("Do you still want to delete it? ( Y / N ): ", std::regex{ "^[YNyn]$" });
			if (ip == "N" || ip == "n") {
				std::cout << "\nDeletion cancelled\n";
				return;
			}
			for (auto e : employyesInDepartment) {
				e.deleteThis();
			}
			if (department->deleteThis()) {	
				std::cout << "\nDeletion Successfull.\n";
			}
			else {
				std::cout << "\nDeletion Failed.\n";
			}

		}
	}
	else {
		std::cout << "No department exist with id: " << id << "\n";
	}
}
void viewDepartments() {
	std::string queryField;
	auto choice{ 0 };

	std::cout << "1. View by ID\n";
	std::cout << "2. View by name\n";
	std::cout << "3. View by manager ID\n";
	std::cout << "4. View All Departments\n\n";

	choice = stoi(input("Please Select an Option: ", std::regex("^[1-4]$")));

	clearDisplay();
	switch (choice) {
	case 1: {
		queryField = input("Please enter id: ", idRegex);
		auto department = Department::getDepartmentById(stoi(queryField));

		clearDisplay();
		if (department) {
			std::cout << "Department with id: " << queryField << "\n";
			department->display();
		}
		else {
			std::cout << "No Department exists with id: " + queryField + "\n";
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

void viewSalaries(){
	std::string queryField;
	auto choice{ 0 };

	std::cout << "1. View by ID\n";
	std::cout << "2. View by first name\n";
	std::cout << "3. View by last name\n";
	std::cout << "4. View by Department\n";
	std::cout << "5. View Salary details of all employees\n\n";

	choice = stoi(input("Please Select an Option: ", std::regex("^[1-5]$")));


	clearDisplay();
	switch (choice) {
	case 1: {
		queryField = input("Please enter ID: ", idRegex);
		auto salary = Salary::getSalaryByID(stoi(queryField));

		clearDisplay();
		if (salary) {
			std::cout << "Salary details of Employee with id: " << queryField << '\n';
			salary->display();
		}
		else {
			std::cout << "No Employee exists with id" << queryField << '\n';
		}
		return;
	}
	case 2: {
		queryField = input("Please enter fisrt name: ");
		auto salariesVector = Salary::getMultipleSalary("firstname", queryField);
		displayVector(salariesVector);
		break;
	}
	case 3: {
		queryField = input("Please enter last name: ");
		auto salariesVector = Salary::getMultipleSalary("lastname", queryField);
		displayVector(salariesVector);
		break;
	}
	case 4: {
		queryField = input("Please enter department name: ");
		auto salariesVector = Salary::getMultipleSalary("department.name", queryField);
		displayVector(salariesVector);
		break;
	}
	case 5: {
		auto salariesVector = Salary::getMultipleSalary();
		displayVector(salariesVector);
		break;
	}
	}
}
void updateSalary(){
	auto id = stoi(input("Please enter id of the employee: ", idRegex));
	auto salary = Salary::getSalaryByID(id);

	if (salary) {
		salary->getUserInputForUpdate();
		salary->update();
	}
	else {
		std::cout << "No Employee exists with id: " << id << '\n';
	}
};


