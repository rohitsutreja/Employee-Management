#pragma once

#include "include/View/Menu.h"
#include "include/Controllers/EmployeeController.h"
#include "include/Controllers/DepartmentController.h"
#include "include/Controllers/EngineerController.h"
#include "include/Controllers/ManagerController.h"
#include "include/Controllers/SalaryController.h"
#include "include/Entities/Table.h"

void runEmployeeMenu() {
	auto choice{ 0 };
	while (1) {
		displayCRUDMenu("Employee");
		choice = stoi(input("\nPlease select an option (1-5): ", std::regex("^[1-5]$")));

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

		choice = stoi(input("\nPlease select an option (1-5): ", std::regex("^[1-5]$")));

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

		choice = stoi(input("Please select an option (1-5): ", std::regex("^[1-5]$")));

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

		choice = stoi(input("\nPlease select an option (1-5): ", std::regex("^[1-5]$")));

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
		std::cout << "3. Increment Salary of an Employee\n";
		std::cout << "4. Main menu\n\n";

		choice = stoi(input("Please select an option (1-4): ", std::regex("^[1-4]$")));

		if (choice == 4) {
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
			case 3:
			{
				incrementSalary();
				waitBeforeClear();
				break;
			}
		}

	}
}

void runTableMenu() {


	while (1) {
		clearDisplay();
		std::cout << "0. Go Back\n";
		std::cout << "1. Create a Table\n";
		std::cout << "2. Delete a Table\n";
		std::cout << "3. View All Tables\n";
		std::cout << "4. Access a Table\n\n";

		auto choice = stoi(input("Enter a choice: ", std::regex("^[0-4]$")));

		if (choice == 0) {
			break;
		}

		clearDisplay();
		switch (choice) {
		case 1: {
			Table t;
			t.getUserInputForTable();

			clearDisplay();
			if (t.save()) std::cout << getInGreen("Creation Successfull.") << '\n';
			else std::cout << getInRed("Creation Failed") << '\n';
			waitBeforeClear();
			break;
		}
		case 2: {
			auto name = input("Enter name: ", nameRegex);

			clearDisplay();
			if (auto t = Table::getTable(name); t) {
				if (t->deleteThis()) std::cout << getInGreen("Deletion Successfull.") << '\n';
				else std::cout << getInRed("Deletion Failed.") << '\n';
			}
			else {
				std::cout << "There is no table with given name in database\n";
			}
			waitBeforeClear();
			break;
		}
		case 3:
		{
			auto tableList = Table::getAllTables();
			for (auto t : tableList) {
				std::cout << "\n->>" << t.getName() << "\n";
				t.displayThis();
			}
			waitBeforeClear();
			break;

		}
		case 4: {

			auto tableList = Table::getAllTables();
			auto noOfTables = std::to_string(tableList.size());


			for (auto t : tableList) {
				std::cout << "o " << " " << t.getName() << '\n';

			}

			auto choice = input("\nPlease enter name of the one of the table : ", nameRegex);

			std::optional<Table> table = Table::getTable(choice);;
			
			if (!table) {
				clearDisplay();
				std::cout << "This table does not exists, please enter valid name\n";
				waitBeforeClear();
				break;
			}


			while (1) {
				clearDisplay();
				std::cout << "0. Go Back\n";
				std::cout << "1. Insert Record\n";
				std::cout << "2. Update Record\n";
				std::cout << "3. View Records\n";
				std::cout << "4. Delete Record\n";
				std::cout << "5. View Table Schema\n\n";

				auto choice = stoi(input("Please enter name of the one of the table : ", std::regex("^[0-5]$")));

				if (choice == 0) {
					break;
				}
				clearDisplay();
				switch (choice) {
				case 1: {

					if (table->insertRecord()) {
						clearDisplay();
						std::cout << getInGreen("Insertion Successfull.") << '\n';
					}
					else {
						clearDisplay();
						std::cout << getInRed("Insertion Failed.") << '\n';
					}
					waitBeforeClear();
					break;
				}
				case 2: {
						if (table->updateRecord()) {
							clearDisplay();
							std::cout << getInGreen("Updation Successfull.") << '\n';
						}
						else {
							clearDisplay();
							std::cout << getInRed("Updation Failed.") << '\n';
						}
					waitBeforeClear();
					break;
				}
				case 3: {
					table->displayAllRecords();
					waitBeforeClear();
					break;

				}
				case 4: {
					if (table->deleteRecord()) {
						clearDisplay();
						std::cout << getInGreen("Deletion Successfull.") << '\n';
					}
					else {
						clearDisplay();
						std::cout << getInRed("Deletion Failed.") << '\n';
					}
					waitBeforeClear();
					break;
				}
				case 5: {
					table->displayThis();
					waitBeforeClear();
					break;
				}
				}
			}
			break;
		}
		}
	}

}

void runMenu() {
	int choice{};

	while (1) {
		displayMainMenu();

		choice = stoi(input("\nPlease select an option (1-7): ", std::regex("^[0-7]$")));

		if (choice == 7) {
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
			case 6:
				clearDisplay();
				runTableMenu();
				break;
		}
	}
}
