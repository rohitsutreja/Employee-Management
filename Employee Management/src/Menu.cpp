#pragma once
#include "../include/Menu.h"
#include "../include/controllers.h"
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
			case 1:
			{
				insertEmployee();
				waitBeforeClear();
				break;
			}
			case 2:
			{
				updateEmployee();
				waitBeforeClear();
				break;
			}
			case 3:
			{
				viewEmployees();
				waitBeforeClear();
				break;
			}
			case 4:
			{
				deleteEmployee();
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
				insertEngineer();
				waitBeforeClear();
				break;
			}

			case 2:
			{
				updateEngineer();
				waitBeforeClear();
				break;
			}

			case 3:
			{	
				viewEngineers();
				waitBeforeClear();
				break;
			}

			case 4:
			{
				deleteEngineer();
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
			{	insertManager();
				waitBeforeClear();
				break;
			}
			case 2:
			{
				updateManager();
				waitBeforeClear();
				break;
			}
			case 3:
			{	viewManagers();
				waitBeforeClear();
				break;
			}
			case 4:
			{
				deleteManager();
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
				insertDepartment();
				waitBeforeClear();
				break;
			}

			case 2:
			{
				updateDepartment();
				waitBeforeClear();
				break;
			}

			case 3:
			{
				viewDepartments();
				waitBeforeClear();
				break;
			}

			case 4:
			{
				deleteDepartment();
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
				viewSalaries();
				waitBeforeClear();
				break;
			}
			case 2:
			{
				updateSalary();
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
