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
				try{
					Controller::insertEmployee();
				}
				catch (const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while insertion of Employee. - ",e.what());
					std::cout << getInRed("Error while insertion of Employee. Please try again!");
				}
				waitBeforeClear();
				break;
			}
			case 2:
			{
				try{
					Controller::updateEmployee();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while updation of Employee. - ",e.what());
					std::cout << getInRed("Error while updation of Employee. Please try again!");
				}			
				waitBeforeClear();
				break;
			}
			case 3:
			{
				try {
					Controller::viewEmployees();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while viewing of Employee. - ",e.what());
					std::cout << getInRed("Error while viewing of Employee. Please try again!");
				}
				waitBeforeClear();
				break;
			}
			case 4:
			{
				try {
					Controller::deleteEmployee();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while deletion of Employee. - ",e.what());
					std::cout << getInRed("Error while deletion of Employee. Please try again!");
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

		choice = stoi(input("\nPlease select an option (1-5): ", std::regex("^[1-5]$")));

		if (choice == 5) {
			break;
		}

		clearDisplay();
		switch (choice) {
			case 1:
			{
				try {
					Controller::insertEngineer();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while insertion of Engineer. - ",e.what());
					std::cout << getInRed("Error while insertion of Engineer. Please try again!");
				}
				
				waitBeforeClear();
				break;
			}

			case 2:
			{
				try {
					Controller::updateEngineer();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while updation of Engineer. - ", e.what());
					std::cout << getInRed("Error while updation of Engineer. Please try again!");
				}

				waitBeforeClear();
				break;
			}

			case 3:
			{	
				try {
					Controller::viewEngineers();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while viewing of Engineer. - ",e.what());
					std::cout << getInRed("Error while viewing of Engineer. Please try again!");
				}
				
				waitBeforeClear();
				break;
			}

			case 4:
			{
				try {
					Controller::deleteEngineer();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while deletion of Engineer. - ",e.what());
					std::cout << getInRed("Error while deletion of Engineer. Please try again!");
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

		choice = stoi(input("Please select an option (1-5): ", std::regex("^[1-5]$")));

		if (choice == 5) {
			break;;
		}

		clearDisplay();
		switch (choice) {
			case 1:
			{	
				try {
					Controller::insertManager();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while insertion of Manager. - ",e.what());
					std::cout << getInRed("Error while insertion of Manager. Please try again!");
				}
				waitBeforeClear();
				break;
			}
			case 2:
			{
				try {
					Controller::updateManager();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while updation of Manager. - ",e.what());
					std::cout << getInRed("Error while updation of Manager. Please try again!");
				}
				waitBeforeClear();
				break;
			}
			case 3:
			{	
				try {
					Controller::viewManagers();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while viewing of Manager. - ",e.what());
					std::cout << getInRed("Error while viewing of Manager. Please try again!");
				}
				
				waitBeforeClear();
				break;
			}
			case 4:
			{
				try {
					Controller::deleteManager();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while deletion of Manager. - ",e.what());
					std::cout << getInRed("Error while deletion of Manager. Please try again!");
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

		choice = stoi(input("\nPlease select an option (1-5): ", std::regex("^[1-5]$")));

		if (choice == 5) {
			break;
		}

		clearDisplay();
		switch (choice) {
			case 1:
			{
				try {
					Controller::insertDepartment();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while insertion of Department. - ",e.what());
					std::cout << getInRed("Error while insertion of Department. Please try again!");
				}
				
				waitBeforeClear();
				break;
			}

			case 2:
			{
				try {
					Controller::updateDepartment();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while updation of Department. - ",e.what());
					std::cout << getInRed("Error while updation of Department. Please try again!");
				}
				waitBeforeClear();
				break;
			}

			case 3:
			{
				try {
					Controller::viewDepartments();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while viewing of Department. - ",e.what());
					std::cout << getInRed("Error while viewing of Department. Please try again!");
				}
				
				waitBeforeClear();
				break;
			}

			case 4:
			{
				try {
					Controller::deleteDepartment();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while deletion of Department. - ",e.what());
					std::cout << getInRed("Error while deletion of Department. Please try again!");
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
				try {
					Controller::viewSalaries();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while viewing of salary. - ",e.what());
					std::cout << getInRed("Error while viewing salary. Please try again!");
				}				
				waitBeforeClear();
				break;
			}
			case 2:
			{
				try {
					Controller::updateSalary();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while updation of salary. - ",e.what());
					std::cout << getInRed("Error while updation of salary. Please try again!");
				}
				
				waitBeforeClear();
				break;
			}
			case 3:
			{
				try {
					Controller::incrementSalary();
				}
				catch(const std::exception& e) {
					clearDisplay();
					MyLogger::error("Error while incrementing of salary. - ",e.what());
					std::cout << getInRed("Error while incrementing salary. Please try again!");
				}
				
				waitBeforeClear();
				break;
			}
		}

	}
}

void runTableMenu()
{
	while (1) {
		try {
			clearDisplay();
			std::cout << "0. Go Back\n";
			std::cout << "1. Create a Table\n";
			std::cout << "2. Delete a Table\n";
			std::cout << "3. View All Tables\n";
			std::cout << "4. Access a Table\n\n";

			auto choice = stoi(input("- Enter a choice: ", std::regex("^[0-4]$")));

			if (choice == 0) {
				break;
			}

			clearDisplay();
			switch (choice) {
			case 1: {
				Table t;
			
				if (!t.getUserInputForTable()) {
					clearDisplay();
					std::cout << getInCyan("- Creation cancelled.");
					waitBeforeClear();
					break;
				}

				clearDisplay();
				if (t.save()) std::cout << getInGreen("Creation successful.") << '\n';
				else std::cout << getInRed("- Creation failed") << '\n';
				waitBeforeClear();
				break;
			}
			case 2: {
				auto name = input("Enter name: ", nameRegex);

				clearDisplay();
				if (auto t = Table::getTable(name); t) {
					if (t->deleteThis()) std::cout << getInGreen("Deletion successful.") << '\n';
					else std::cout << getInRed("Deletion failed.") << '\n';
				}
				else {
					std::cout << getInCyan("There is no table with given name in database\n");
				}
				waitBeforeClear();
				break;
			}
			case 3:{
				auto tableList = Table::getAllTables();
				for (const auto& t : tableList) {
					std::cout << "\n->>" << t.getName() << "\n";
					t.display();
				}
				waitBeforeClear();
				break;

			}
			case 4: {
				auto tableList = Table::getAllTables();

				for (const auto& t : tableList) {
					std::cout << "o " << " " << t.getName() << '\n';
				}

				auto choice = input("\n- Please enter name of the one of the table : ", nameRegex);

				std::optional<Table> table = Table::getTable(choice);;

				if (!table) {
					clearDisplay();
					std::cout << "- This table does not exists, please enter valid name\n";
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

					auto choice = stoi(input("Please enter an option : ", std::regex("^[0-5]$")));

					if (choice == 0) {
						break;
					}
					clearDisplay();
					switch (choice) {
					case 1: {

						if (table->insertRecord()) {
							clearDisplay();
							std::cout << getInGreen("Insertion successful.") << '\n';
						}
						else {
							clearDisplay();
							std::cout << getInRed("Insertion failed.") << '\n';
						}
						waitBeforeClear();
						break;
					}
					case 2: {
						if (table->updateRecord()) {
							clearDisplay();
							std::cout << getInGreen("Updation successful.") << '\n';
						}
						else {
							clearDisplay();
							std::cout << getInRed("Updation failed.") << '\n';
						}
						waitBeforeClear();
						break;
					}
					case 3: {
						std::cout << "0. Go Back\n";
						std::cout << "1. View all records.\n";
						std::cout << "2. Filter records.\n\n";

						auto choice = input("Please enter an option: ", std::regex("^[1-2]$"));
						
						clearDisplay();
						if (choice == "0") {
							break;
						}
						else if (choice == "1") {
							table->displayAllRecords();
						}
						else {
							table->displayFilteredRecords();
						}
						

						waitBeforeClear();
						break;
					}
					case 4: {
						if (table->deleteRecord()) {
							clearDisplay();
							std::cout << getInGreen("Deletion successful.") << '\n';
						}
						else {
							clearDisplay();
							std::cout << getInRed("Deletion failed.") << '\n';
						}
						waitBeforeClear();
						break;
					}
					case 5: {
						table->display();
						waitBeforeClear();
						break;
					}
					}
				}
				break;
			}
			}
		}
		catch (const std::exception& e) {
			clearDisplay();
			MyLogger::error("Error in table menu Please try again! - ", e.what());
			std::cout << getInRed("Unexpected Error. Please try again.") << '\n';
			waitBeforeClear();
		}
	}
}

void exportToCSV() {
	try {
		clearDisplay();
		if (Table::writeCSV()) {
			std::cout << getInGreen("Tables exported successfully\n");
		}
		else {
			std::cout << getInRed("CSV Export failed\n");
		}
		waitBeforeClear();
	}
	catch(std::exception& e){
		clearDisplay();
		MyLogger::error("Error in exporting to csv. - ", e.what());
		std::cout << getInRed("Unexpected Error. Please try again.") << '\n';
		waitBeforeClear();
	}
	
	
}

void runMenu() {
	int choice{};

	while (1) {
		displayMainMenu();

		choice = stoi(input("\nPlease select an option (1-7): ", std::regex("^[0-8]$")));

		if (choice == 8) {
			displayThanks();
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
			case 7:
				clearDisplay();
				exportToCSV();
				break;
				
		}
	}
}
