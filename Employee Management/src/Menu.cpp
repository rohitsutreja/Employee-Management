#pragma once
#include "../include/Menu.h"
void runEmployeeMenu() {
	auto choice{ 0 };
	while (1) {
		displayCRUDMenu("Employee");
		choice = stoi(input("\nPlease select an option: ", std::regex("^[1-5]$")));

		clearDisplay();

		if (choice == 5) {
			break;
		}

		switch (choice) {
			//Insert
		case 1:
		{
			Employee employee;
			employee.getUserInput();

			clearDisplay();

			if (auto duplicateEmployee = Employee::getEmployeeById(employee.getId()); duplicateEmployee) {
				std::cout << "This employee id already exists, Please try again with another id.\n";
				waitBeforeClear();
				break;
			}
			auto department = Department::getDepartmentById(employee.getDepartmentId());
			auto manager = Manager::getManagerById(employee.getManagerId());
			if (!department) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
				waitBeforeClear();
				break;
			}
			if (employee.getManagerId() != -1 && !manager) {
				std::cout << "This manager does not exist, Please try again with valid manager id or without manager\n";
				waitBeforeClear();
				break;
			}
			if (employee.save()) {
				std::cout << "Insertion Successfull.\n";
			}
			else {
				std::cout << "Insertion Failed\n";
			};
			waitBeforeClear();
			break;
		}

		//Update
		case 2:
		{
			auto id = stoi(input("Please enter id of the employee: ", idRegex));
			auto employee = Employee::getEmployeeById(id);


			clearDisplay();
			if (employee) {
				auto oldMid = employee->getManagerId();
				auto oldDid = employee->getDepartmentId();

				employee->getUserInputForUpdate();
				clearDisplay();

				auto newMid = employee->getManagerId();
				auto newDid = employee->getDepartmentId();

				if (oldDid != newDid) {
					auto department = Department::getDepartmentById(employee->getDepartmentId());
					if (!department) {
						std::cout << "This department does not exist, Please try again with valid department id\n";
						waitBeforeClear();
						break;
					}
				}

				if (oldMid != newMid) {
					auto manager = Manager::getManagerById(employee->getManagerId());
					if (!manager) {
						std::cout << "This manager does not exist, Please try again with valid manager id\n";
						waitBeforeClear();
						break;
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
			waitBeforeClear();
			break;
		}

		//View
		case 3:
		{
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
				break;
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

				waitBeforeClear();
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
			break;
		}

		//Delete
		case 4:
		{
			int id = stoi(input("Please enter Id of the employee: ", idRegex));
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

			waitBeforeClear();
			break;
		}
		}
	}
}

void runEngineerMenu() {
	auto choice{ 0 };
	while (1) {
		displayCRUDMenu("Engineer");

		choice = stoi(input("Please select an option: ", std::regex("^[1-5]$")));

		if (choice == 5) {
			break;
		}

		clearDisplay();
		switch (choice) {
		case 1:
		{
			Engineer engineer;
			engineer.getUserInput();

			clearDisplay();
			if (auto duplicateEngineer = Engineer::getEngineerById(engineer.getId()); duplicateEngineer) {
				std::cout << "This employee id already exists, Please try again with another id.\n";
				waitBeforeClear();
				break;
			}

			auto department = Department::getDepartmentById(engineer.getDepartmentId());
			auto manager = Manager::getManagerById(engineer.getManagerId());
			if (!department) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
			}
			else {
				if (engineer.getManagerId() != -1 && !manager) {
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
			waitBeforeClear();
			break;
		}

		case 2:
		{

			auto id = stoi(input("Please enter id of the engineer: ", idRegex));
			auto engineer = Engineer::getEngineerById(id);

			if (engineer) {
				auto oldMid = engineer->getManagerId();
				auto oldDid = engineer->getDepartmentId();

				engineer->getUserInputForUpdate();

				clearDisplay();

				auto newMid = engineer->getManagerId();
				auto newDid = engineer->getDepartmentId();

				if (oldDid != newDid) {
					auto department = Department::getDepartmentById(newDid);
					if (!department) {
						std::cout << "This department does not exist, Please try again with valid department id\n";
						waitBeforeClear();
						break;
					}
				}

				if (oldMid != newMid) {
					auto manager = Manager::getManagerById(newMid);
					if (!manager) {
						std::cout << "This manager does not exist, Please try again with valid manager id\n";
						waitBeforeClear();
						break;
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
			waitBeforeClear();
			break;
		}

		case 3:
		{
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

				waitBeforeClear();
				break;
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
			break;
		}

		case 4:
		{
			int id = stoi(input("Please enter id of the engineer: ", idRegex));
			auto engineer = Engineer::getEngineerById(id);

			clearDisplay();
			if (engineer.has_value()) {
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

			waitBeforeClear();
			break;
		}
		}
	}
}

void runManagerMenu() {
	auto choice{ 0 };
	while (1) {
		displayCRUDMenu("Manager");

		choice = stoi(input("Please select an option: ", std::regex("^[1-5]$")));

		if (choice == 5) {
			break;;
		}

		clearDisplay();
		switch (choice) {
		case 1:
		{

			Manager manager;
			manager.getUserInput();

			clearDisplay();
			if (auto duplicateManager = Manager::getManagerById(manager.getId()); duplicateManager) {
				std::cout << "This employee id already exists, Please try again with another id.\n";
				waitBeforeClear();
				break;
			}


			auto department = Department::getDepartmentById(manager.getDepartmentId());
			auto managerOfManager = Manager::getManagerById(manager.getManagerId());

			if (!department) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
			}
			else {
				if (manager.getManagerId() != -1 && !managerOfManager) {
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
			waitBeforeClear();
			break;
		}

		case 2:
		{

			auto id = stoi(input("Please enter Id of the Manager: ", idRegex));
			auto manager = Manager::getManagerById(id);

			clearDisplay();
			if (manager) {
				auto oldMid = manager->getManagerId();
				auto oldDid = manager->getDepartmentId();

				manager->getUserInputForUpdate();

				clearDisplay();

				auto newMid = manager->getManagerId();
				auto newDid = manager->getDepartmentId();

				if (oldDid != newDid) {
					auto department = Department::getDepartmentById(manager->getDepartmentId());
					if (!department) {
						std::cout << "This department does not exist, Please try again with valid department id\n";
						waitBeforeClear();
						break;
					}
				}

				if (oldMid != newMid) {
					auto managerOfManager= Manager::getManagerById(manager->getManagerId());
					if (!managerOfManager) {
						std::cout << "This manager does not exist, Please try again with valid manager id\n";
						waitBeforeClear();
						break;
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
			waitBeforeClear();
			break;
		}

		case 3:
		{
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

				waitBeforeClear();
				break;

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
			break;
		}

		case 4:
		{
			int id = stoi(input("Please enter Id of the Manager: ", idRegex));
			auto manager = Manager::getManagerById(id);

			clearDisplay();
			if (manager) {
				if (manager->deleteThis()) {
					std::cout << "Deletion Successfull.\n";
				}
				else {
					std::cout << "Deletion Failed.\n";
				}

			}
			else {
				std::cout << "No manager exist with id: " << id << "\n";
			}

			waitBeforeClear();
			break;
		}
		}
	}
}

void runDepartmentMenu() {
	auto choice{ 0 };
	while (1) {
		displayCRUDMenu("Department");

		choice = stoi(input("Please select an option: ", std::regex("^[1-5]$")));

		if (choice == 5) {
			break;
		}

		clearDisplay();
		switch (choice) {
		case 1:
		{

			Department department;
			department.getUserInput();


			clearDisplay();
			if (auto duplicateDepartment = Department::getDepartmentById(department.getId()); duplicateDepartment) {
				std::cout << "This employee id already exists, Please try again with another id.\n";
				waitBeforeClear();
				break;
			}

			if (department.save()) {
				std::cout << "Insertion Successfull.\n";
			}
			else {
				std::cout << "Insertion Failed.\n";
			};

			waitBeforeClear();
			break;
		}

		case 2:
		{
			int id = stoi(input("Please enter Id of the Department: ", idRegex));
			auto department = Department::getDepartmentById(id);

			clearDisplay();
			if (department) {
				auto oldMid = department->getManagerId();
				department->getUserInputForUpdate();
				auto newMid = department->getManagerId();

				clearDisplay();
				if (oldMid != newMid) {
					if (auto manager = Manager::getManagerById(newMid); !manager) {
						std::cout << "No Manager exists with this id, Please retry with valid manager id\n";
						waitBeforeClear();
						break;
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

			waitBeforeClear();
			break;
		}

		case 3:
		{
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
				waitBeforeClear();
				break;
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

			break;
		}

		case 4:
		{

			int id = stoi(input("Please enter Id of the Department: ", idRegex));
			auto department = Department::getDepartmentById(id);

			clearDisplay();
			if (department) {
				if (department->deleteThis()) {
					std::cout << "Deletion Successfull.\n";
				}
				else {
					std::cout << "Deletion Failed.\n";
				}

			}
			else {
				std::cout << "No department exist with id: " << id << "\n";
			}

			waitBeforeClear();
			break;
		}
		}

	}

}

void runSalaryMenu() {
	auto choice{ 0 };
	while (1) {
		clearDisplay();
		std::cout << "1. View Salary details of an Employee\n";
		std::cout << "2. Update Salary details of an Employee\n";
		std::cout << "3. Main menu\n\n";

		choice = stoi(input("Please select an option: ", std::regex("^[1-3]$")));

		if (choice == 3) {
			break;
		}

		clearDisplay();
		switch (choice) {

		case 1:
		{
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
				waitBeforeClear();
				break;
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
			break;
		}

		case 2:
		{
			auto id = stoi(input("Please enter id of the employee: ", idRegex));
			auto salary = Salary::getSalaryByID(id);

			if (salary) {
				salary->getUserInputForUpdate();
				salary->update();
			}
			else {
				std::cout << "No Employee exists with id: " << id << '\n';
			}
			waitBeforeClear();
			break;
		}
		}

	}
}

void runMenu() {
	int choice{};

	while (1) {
		displayMainMenu();

		choice = stoi(input("Please Select an Option: ", mainChoiceRegex));

		if (choice == 6) {
			break;
		}

		switch (choice) {
		case 1:
			clearDisplay();
			runEmployeeMenu();
			break;
		case 2:
			clearDisplay();
			runDepartmentMenu();
			break;
		case 3:
			clearDisplay();
			runEngineerMenu();
			break;
		case 4:
			clearDisplay();
			runManagerMenu();
			break;
		case 5:
			clearDisplay();
			runSalaryMenu();
			break;
		}

	}
}
