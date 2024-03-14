#include <iostream>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include"include/Employee.h"
#include "include/DB.h"
#include "include/Regex.h"
#include "include/Department.h"
#include "include/Engineer.h"
#include "include/Manager.h"
#include "include/Logger/MyLogger.h"


void runEmployeeMenu() {
	auto choice{0};
	while (1) {
		system("CLS");
		std::cout << "1. Insert an Employee\n";
		std::cout << "2. Update an Employee\n";
		std::cout << "3. View an Employee\n";
		std::cout << "4. Delete an Employee\n";
		std::cout << "5. Main menu\n";

		choice = stoi(input("\nPlease select an option: ", std::regex("^[1-5]$")));
		system("CLS");

		//Quit
		if (choice == 5) {
			break;
		}

		switch (choice) {
			//Insert
			case 1:
			{
				Employee e;
				e.getUserInput();

				system("CLS");
				if (e.save()) {
					std::cout << "Insertion Successfull.\n";
				}
				else {
					std::cout << "Insertion Failed.\n";
				};

				std::cout << "\nPress Enter to continue...\n";
				std::cin.get();
				break;
			}

			//Update
			case 2:
			{
				auto id = stoi(input("Please enter id of the employee: ", idRegex));
				auto e = Employee::getEmployeeById(id);

				system("CLS");
				if (e.has_value()) {
					e.value().getUserInputForUpdate();
					if (e.value().update()) {
						std::cout << "Updation Successfull.\n";
					}
					else {
						std::cout << "Updation Failed.\n";
					}
				}
				else {
					std::cout << "No employee exist with id: " << id << "\n";
				}

				std::cout << "\nPress Enter to continue...\n";
				std::cin.get();
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

				choice = stoi(input("Please Select an Option: ",std::regex("^[0-5]$")));

				if (choice == 0) {
					break;
				}

				system("CLS");
				switch (choice) {
				case 1: {
					queryField = input("Please enter id: ", idRegex);
					auto e = Employee::getEmployeeById(stoi(queryField));
				
					system("CLS");
					if (e.has_value()) {
						std::cout << "Employee with id: " << queryField << '\n';
						e.value().display();
					}
					else {
						std::cout << "No Employee exist with id: "  << queryField << "\n";
					}

					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 2: {
					queryField = input("Please enter fisrt name: ");
					auto vec = Employee::getMultipleEmployee("firstname", queryField);

					system("CLS");
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto e : vec) {
						e.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 3: {
					queryField = input("Please enter last name: ");
					auto vec = Employee::getMultipleEmployee("lastname", queryField);

					system("CLS");
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto e : vec) {
						e.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 4: {
					queryField = input("Please enter department name: ");
					auto vec = Employee::getMultipleEmployee("department.name", queryField);

					system("CLS");
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto e : vec) {
						e.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 5: {
					auto vec = Employee::getMultipleEmployee();
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto e : vec) {
						e.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				}

				break;
			}

			//Delete
			case 4:
			{
				int id = stoi(input("Please enter Id of the employee: ", idRegex));
				auto e = Employee::getEmployeeById(id);
				if (e.has_value()) {
					if (e.value().deleteThis()) {
						std::cout << "Employee with id: " << id <<  "deleted successfully.\n";
					}
					else {
						std::cout << "Employee couldn't be deleted\n";
					}

				}
				else {
					std::cout << "No Employee exist with id: " << id <<"\n";
				}

				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
		}
	}
}

void runEngineerMenu(){
	auto choice{ 0 };
	while (1) {
		system("CLS");
		std::cout << "1. Insert an Engineer\n";
		std::cout << "2. Update an Engineer\n";
		std::cout << "3. View an Engineer\n";
		std::cout << "4. Delete an Engineer\n";
		std::cout << "5. Main menu\n";

		choice = stoi(input("Please select an option: ", std::regex("^[1-5]$")));

		

		if (choice == 5) {
			break;
		}

		system("CLS");
		switch (choice) {
		case 1:
		{
			Engineer e;
			e.getUserInput();

			system("CLS");
			if (e.save()) {
				std::cout << "Insertion Successfull.\n";
			}
			else {
				std::cout << "Insertion Failed.\n";
			};

			std::cout << "\nPress Enter to continue...\n";
			std::cin.get();
			break;
		}

		case 2:
		{
			auto id = stoi(input("Please enter Id of the engineer: ", idRegex));
			auto e = Engineer::getEngineerByID(id);

			system("CLS");

			if (e.has_value()) {
				e.value().getUserInputForUpdate();
				if (e.value().update()) {
					std::cout << "Updation Successfull.\n";
				}
				else {
					std::cout << "Updation Failed.\n";
				}
			}
			else {
				std::cout << "No engineer exist with id: " << id << "\n";
			}

			std::cout << "\nPress Enter to continue...\n";
			std::cin.get();
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

			choice = stoi(input("Please Select an Option: ",std::regex("^[1-6]$")));

			system("CLS");
			switch (choice) {
			case 1: {

				queryField = input("Please enter id: ", idRegex);
				auto e = Engineer::getEngineerByID(stoi(queryField));

				system("CLS");
				if (e.has_value()) {
					std::cout << "Engineer with id: " << queryField << '\n';
					e.value().display();
				}
				else {
					std::cout << "No engineer exist with id: " << queryField << "\n";
				}

				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 2: {
				queryField = input("Please enter fisrt name: ");
				auto vec = Engineer::getMultipleEngineers("firstname", queryField);

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 3: {
				queryField = input("Please enter last name: ");
				auto vec = Engineer::getMultipleEngineers("lastname", queryField);
				

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 4: {
				queryField = input("Please enter department name: ");
				auto vec = Engineer::getMultipleEngineers("department.name", queryField);

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 5: {
				auto vec = Engineer::getMultipleEngineers();

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 6: {
				queryField = input("Please enter programming language: ");
				auto vec = Engineer::getMultipleEngineers("programming_language", queryField);

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			}
			break;
		}
		
		case 4:
		{
			int id = stoi(input("Please enter id of the engineer: ", idRegex));
			auto e = Engineer::getEngineerByID(id);

			system("CLS");
			if (e.has_value()) {
				if (e.value().deleteThis()) {
					std::cout << "Deletion Successfull.\n";
				}
				else {
					std::cout << "Deletion Failed.\n";
				}

			}
			else {
				std::cout << "No engineer exist with id: " << id << "\n";
			}

			std::cout << "\nPress Enter to continue...";
			std::cin.get();
			break;
		}
		}	
	}		
}

void runManagerMenu() {
	auto choice{ 0 };
	while (1) {
		system("CLS");
		std::cout << "1. Insert an Manager\n";
		std::cout << "2. Update an Manager\n";
		std::cout << "3. View an Manager\n";
		std::cout << "4. Delete an Manager\n";
		std::cout << "5. Main menu\n\n";

		choice = stoi(input("Please select an option: ", std::regex("^[1-5]$")));

		if (choice== 5) {
			break;;
		}

		system("CLS");
		switch (choice) {
		case 1:
		{

			Manager m;
			m.getUserInput();

			system("CLS");
			if (m.save()) {
				std::cout << "Insertion Successfull.\n";
			}
			else {
				std::cout << "Insertion Failed.\n";
			};

			std::cout << "\nPress Enter to continue...\n";
			std::cin.get();
			break;
		}

		case 2:
		{

			auto id = stoi(input("Please enter Id of the Manager: ", idRegex));
			auto m = Manager::getManagerByID(id);

			system("CLS");

			if (m.has_value()) {
				m.value().getUserInputForUpdate();
				if (m.value().update()) {
					std::cout << "Updation Successfull.\n";
				}
				else {
					std::cout << "Updation Failed.\n";
				}
			}
			else {
				std::cout << "No manager exist with id: " << id << "\n";
			}

			std::cout << "\nPress Enter to continue...\n";
			std::cin.get();
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

			system("CLS");
			switch (choice) {
			case 1: {

				queryField = input("Please enter ID: ", idRegex);
				auto m = Manager::getManagerByID(stoi(queryField));

				system("CLS");
				if (m.has_value()) {
					std::cout << "Manager with id: " << queryField << '\n';
					m.value().display();
				}
				else {
					std::cout << "No manager exist with id: " << queryField << "\n";
				}

				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;

			}
			case 2: {
				queryField = input("Please enter fisrt name: ");
				auto vec = Manager::getMultipleManagers("firstname", queryField);

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 3: {
				queryField = input("Please enter last name: ");
				auto vec = Manager::getMultipleManagers("lastname", queryField);

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 4: {
				queryField = input("Please enter department name: ");
				auto vec = Manager::getMultipleManagers("department.name", queryField);

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			case 5: {
				auto vec = Manager::getMultipleManagers();

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			}
			break;
		}

		case 4:
		{
			int id = stoi(input("Please enter Id of the Manager: ", idRegex));
			auto m = Manager::getManagerByID(id);

			system("CLS");
			if (m.has_value()) {
				if (m.value().deleteThis()) {
					std::cout << "Deletion Successfull.\n";
				}
				else {
					std::cout << "Deletion Failed.\n";
				}

			}
			else {
				std::cout << "No manager exist with id: " << id << "\n";
			}

			std::cout << "\nPress Enter to continue...";
			std::cin.get();
			break;
		}
		}	
	}	
}

void runDepartmentMenu(){
	auto choice{0};
	while (1) {
		std::cout << "1. Insert Department\n";
		std::cout << "2. Update Department\n";
		std::cout << "3. View Department\n";
		std::cout << "4. Delete Department\n";
		std::cout << "5. Main menu\n\n";

		choice = stoi(input("Please select an option: ", std::regex("^[1-5]$")));

		if (choice == 5) {
			break;
		}

		system("CLS");
		switch (choice) {
			case 1:
			{	

				Department d;
				d.getUserInput();

				system("CLS");
				if (d.save()) {
					std::cout << "Insertion Successfull.\n";
				}
				else {
					std::cout << "Insertion Failed.\n";
				};

				std::cout << "\nPress Enter to continue...\n";
				std::cin.get();
				break;
			}

			case 2:
			{
				int id = stoi(input("Please enter Id of the Department: ", idRegex));
				auto d = Department::getDepartment(id);

				system("CLS");
				if (d.has_value()) {
					d.value().getUserInputForUpdate();
					if (d.value().update()) {
						std::cout << "Updation Successfull.\n";
					}
					else {
						std::cout << "Updation Failed.\n";
					}
				}
				else {
					std::cout << "No department exist with id: " << id << "\n";
				}

				std::cout << "\nPress Enter to continue...\n";
				std::cin.get();
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

				system("CLS");
				switch (choice) {
					case 1: {
						queryField = input("Please enter id: ", idRegex);
						auto d = Department::getDepartment(stoi(queryField));
						
						system("CLS");
						if (d.has_value()) {
							std::cout << "Department with id: " << queryField << "\n";
							d.value().display();
						}
						else {
							std::cout << "No Department exists with id: " + queryField + "\n";
						}
						std::cout << "\nPress Enter to continue...";
						std::cin.get();
						break;
					}
					case 2: {
						queryField = input("Please enter name: ");
						auto vec = Department::getMultipleDepartment("name", queryField);

						system("CLS");
						std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
						for (auto d : vec) {
							d.display();
							std::cout << '\n';
						}
						std::cout << "\nPress Enter to continue...";
						std::cin.get();
						break;
					}
					case 3: {
						queryField = input("Please enter manager ID: ");
						auto vec = Department::getMultipleDepartment("Department.manager_id", queryField);

						system("CLS");
						std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
						for (auto d : vec) {
							d.display();
							std::cout << '\n';
						}
						std::cout << "\nPress Enter to continue...";
						std::cin.get();
						break;
					}
					case 4: {


					auto vec = Department::getMultipleDepartment();

					system("CLS");
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto d : vec) {
						d.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				}

				break;
			}

			case 4:
			{	

				int id = stoi(input("Please enter Id of the Department: ", idRegex));
				auto d = Department::getDepartment(id);

				system("CLS");
				if (d.has_value()) {
					if (d.value().deleteThis()) {
						std::cout << "Deletion Successfull.\n";
					}
					else {
						std::cout << "Deletion Failed.\n";
					}

				}
				else {
					std::cout << "No department exist with id: " << id << "\n";
				}

				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
		}
	
	}
	
}

void runSalaryMenu() {
	auto choice{ 0 };

	while (1) {
		std::cout << "1. View Salary details of an Employee\n";
		std::cout << "2. Update Salary details of an Employee\n";
		std::cout << "3. Main menu\n\n";

		choice = stoi(input("Please select an option: ", std::regex("^[1-3]$")));

		if (choice == 3) {
			break;
		}

		system("CLS");
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


			system("CLS");
			switch (choice) {
				case 1: {
					queryField = input("Please enter ID: ", idRegex);
					auto e = Salary::getSalaryByID(stoi(queryField));
					
					system("CLS");
					if (e.has_value()) {
						std::cout << "Salary details of Employee with id: " << queryField << '\n';
						e.value().display();
					}
					else {
						std::cout << "No Employee exists with id" << queryField << '\n';
					}

					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 2: {
					queryField = input("Please enter fisrt name: ");
					auto vec = Salary::getMultipleSalary("firstname", queryField);

					system("CLS");
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto e : vec) {
						e.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 3: {
					queryField = input("Please enter last name: ");
					auto vec = Salary::getMultipleSalary("lastname", queryField);

					system("CLS");
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto e : vec) {
						e.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 4: {
					queryField = input("Please enter department name: ");
					auto vec = Salary::getMultipleSalary("department.name", queryField);

					system("CLS");
					std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
					for (auto e : vec) {
						e.display();
						std::cout << '\n';
					}
					std::cout << "\nPress Enter to continue...";
					std::cin.get();
					break;
				}
				case 5: {


				auto vec = Salary::getMultipleSalary();

				system("CLS");
				std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
				for (auto e : vec) {
					e.display();
					std::cout << '\n';
				}
				std::cout << "\nPress Enter to continue...";
				std::cin.get();
				break;
			}
			}
			break;
		}

		case 2:
		{
			auto id = stoi(input("Please enter id of the employee: ", idRegex));
			auto e = Salary::getSalaryByID(id);

			if (e.has_value()) {
				e.value().getUserInputForUpdate();
				e.value().update();
			}
			else {
				std::cout << "No Employee exists with id: " << id << '\n';
			}

			std::cout << "\nPress Enter to continue...";
			std::cin.get();
			break;
		}
		}

	}


	
}

void runMenu() {
	int choice{};
	
	while (1) {
		system("CLS");
		std::cout << "\n<--------------------------------------------> EMPLOYEE MANAGEMENT SYSTEM <-------------------------------------------->\n";
		std::cout << "\n1. Employee Menu\n";
		std::cout << "2. Department Menu\n";
		std::cout << "3. Engineer Menu\n";
		std::cout << "4. Manager Menu\n";
		std::cout << "5. Salary Menu\n";
		std::cout << "6. Quit\n\n";

		choice = stoi(input("Please Select an Option: ",mainChoiceRegex));

		if (choice == 1) {
			system("CLS");
			runEmployeeMenu();
		}
		else if (choice == 2) {
			system("CLS");
			runDepartmentMenu();

		}
		else if (choice == 3) {
			system("CLS");
			runEngineerMenu();
		}
		else if (choice == 4) {
			system("CLS");
			runManagerMenu();
		}
		else if (choice == 5) {
			system("CLS");
			runSalaryMenu();

		}
		else if (choice == 6) {
			std::cout << "Thank You\n";
			break;
		}
	}
}

int main()
{
	runMenu();
	return 0;
}
