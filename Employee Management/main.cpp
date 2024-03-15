#include <iostream>
#include "sqlite/sqlite3.h"
#include "include/Employee.h"
#include "include/DB.h"
#include "include/Regex.h"
#include "include/Department.h"
#include "include/Engineer.h"
#include "include/Manager.h"
#include "include/Logger/MyLogger.h"
#include "include/Util.h"

void runEmployeeMenu() {
	auto choice{0};
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
				Employee e;
				e.getUserInput();

				auto d = Department::getDepartment(e.getDepartmentId());
				auto m = Manager::getManagerByID(e.getManagerId());

				clearDisplay();
				if (!d) {
					std::cout << "This department does not exist, Please try again with valid department id\n";
					waitBeforeClear();
					break;
				}
				if (e.getManagerId() != -1 && !m) {
					std::cout << "This manager does not exist, Please try again with valid manager id or without manager\n";
					waitBeforeClear();
					break;
				}
			    if (e.save()) {
					std::cout << "Insertion Successfull.\n";
				}
				else {
					std::cout << "Insertion Failed.\n";
				};
				waitBeforeClear();
				break;
			}

			//Update
			case 2:
			{
				auto id = stoi(input("Please enter id of the employee: ", idRegex));
				auto e = Employee::getEmployeeById(id);

				
				clearDisplay();
				if (e.has_value()) {
					auto oldMid = e->getManagerId();
					auto oldDid = e->getDepartmentId();

					e.value().getUserInputForUpdate();
					clearDisplay();

					auto newMid = e->getManagerId();
					auto newDid = e->getDepartmentId();

					if (oldDid != newDid) {
						auto d = Department::getDepartment(e->getDepartmentId());
						if (!d) {
							std::cout << "This department does not exist, Please try again with valid department id\n";
							waitBeforeClear();
							break;
						}
					}
					
					if (oldMid != newMid) {
						auto m = Manager::getManagerByID(e->getManagerId());
						if (!m) {
							std::cout << "This manager does not exist, Please try again with valid manager id\n";
							waitBeforeClear();
							break;
						}
					}
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

				choice = stoi(input("Please Select an Option: ",std::regex("^[0-5]$")));

				if (choice == 0) {
					break;
				}

				clearDisplay();
				switch (choice) {
					case 1: {
						queryField = input("Please enter id: ", idRegex);
						auto e = Employee::getEmployeeById(stoi(queryField));
				
						clearDisplay();
						if (e.has_value()) {
							std::cout << "Employee with id: " << queryField << '\n';
							e.value().display();
						}
						else {
							std::cout << "No Employee exist with id: "  << queryField << "\n";
						}

						waitBeforeClear();
						break;
					}
					case 2: {
						queryField = input("Please enter fisrt name: ");
						auto vec = Employee::getMultipleEmployee("firstname", queryField);
						displayVector(vec);
						break;
					}
					case 3: {
						queryField = input("Please enter last name: ");
						auto vec = Employee::getMultipleEmployee("lastname", queryField);
						displayVector(vec);
						break;
					}
					case 4: {
						queryField = input("Please enter department name: ");
						auto vec = Employee::getMultipleEmployee("department.name", queryField);
						displayVector(vec);
						break;
					}
					case 5: {
					auto vec = Employee::getMultipleEmployee();
					displayVector(vec);
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

				waitBeforeClear();
				break;
			}
		}
	}
}

void runEngineerMenu(){
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
			Engineer e;
			e.getUserInput();

			auto d = Department::getDepartment(e.getDepartmentId());
			auto m = Manager::getManagerByID(e.getManagerId());
			clearDisplay();
			if (!d) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
			}
			else {
				if (e.getManagerId() != -1 && !m) {
					std::cout << "This manager does not exist, Please try again with valid manager id or without manager\n";
				}
				else {
					if (e.save()) {
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
			auto e = Engineer::getEngineerByID(id);

			if (e.has_value()) {
				auto oldMid = e->getManagerId();
				auto oldDid = e->getDepartmentId();

				e.value().getUserInputForUpdate();
				
				clearDisplay();

				auto newMid = e->getManagerId();
				auto newDid = e->getDepartmentId();

				if (oldDid != newDid) {
					auto d = Department::getDepartment(newDid);
					if (!d) {
						std::cout << "This department does not exist, Please try again with valid department id\n";
						waitBeforeClear();
						break;
					}
				}

				if (oldMid != newMid) {
					auto m = Manager::getManagerByID(newMid);
					if (!m) {
						std::cout << "This manager does not exist, Please try again with valid manager id\n";
						waitBeforeClear();
						break;
					}
				}
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
			waitBeforeClear();
			break;


			clearDisplay();

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

			choice = stoi(input("Please Select an Option: ",std::regex("^[1-6]$")));

			clearDisplay();
			switch (choice) {
			case 1: {

				queryField = input("Please enter id: ", idRegex);
				auto e = Engineer::getEngineerByID(stoi(queryField));

				clearDisplay();
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

				displayVector(vec);
				break;
			}
			case 3: {
				queryField = input("Please enter last name: ");
				auto vec = Engineer::getMultipleEngineers("lastname", queryField);
				

				displayVector(vec);
				break;
			}
			case 4: {
				queryField = input("Please enter department name: ");
				auto vec = Engineer::getMultipleEngineers("department.name", queryField);

				displayVector(vec);
				break;
			}
			case 5: {
				auto vec = Engineer::getMultipleEngineers();

				displayVector(vec);
				break;
			}
			case 6: {
				queryField = input("Please enter programming language: ");
				auto vec = Engineer::getMultipleEngineers("programming_language", queryField);

				displayVector(vec);
				break;
			}
			}
			break;
		}
		
		case 4:
		{
			int id = stoi(input("Please enter id of the engineer: ", idRegex));
			auto e = Engineer::getEngineerByID(id);

			clearDisplay();
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

		if (choice== 5) {
			break;;
		}

		clearDisplay();
		switch (choice) {
		case 1:
		{

			Manager m;
			m.getUserInput();

			auto d = Department::getDepartment(m.getDepartmentId());
			auto mm = Manager::getManagerByID(m.getManagerId());
			clearDisplay();
			if (!d) {
				std::cout << "This department does not exist, Please try again with valid department id\n";
			}
			else {
				if (m.getManagerId() != -1 && !mm) {
					std::cout << "This manager of manager does not exist, Please try again with valid manager id or without manager\n";
				}
				else {
					if (m.save()) {
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
			auto m = Manager::getManagerByID(id);

			clearDisplay();
			if (m) {
				auto oldMid = m->getManagerId();
				auto oldDid = m->getDepartmentId();

				m->getUserInputForUpdate();

				clearDisplay();

				auto newMid = m->getManagerId();
				auto newDid = m->getDepartmentId();

				if (oldDid != newDid) {
					auto d = Department::getDepartment(m->getDepartmentId());
					if (!d) {
						std::cout << "This department does not exist, Please try again with valid department id\n";
						waitBeforeClear();
						break;
					}
				}

				if (oldMid != newMid) {
					auto mm = Manager::getManagerByID(m->getManagerId());
					if (!mm) {
						std::cout << "This manager does not exist, Please try again with valid manager id\n";
						waitBeforeClear();
						break;
					}
				}
				if (m->update()) {
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
				auto m = Manager::getManagerByID(stoi(queryField));

				clearDisplay();
				if (m.has_value()) {
					std::cout << "Manager with id: " << queryField << '\n';
					m.value().display();
				}
				else {
					std::cout << "No manager exist with id: " << queryField << "\n";
				}

				waitBeforeClear();
				break;

			}
			case 2: {
				queryField = input("Please enter fisrt name: ");
				auto vec = Manager::getMultipleManagers("firstname", queryField);

				displayVector(vec);
				break;
			}
			case 3: {
				queryField = input("Please enter last name: ");
				auto vec = Manager::getMultipleManagers("lastname", queryField);
				displayVector(vec);
				break;
			}
			case 4: {
				queryField = input("Please enter department name: ");
				auto vec = Manager::getMultipleManagers("department.name", queryField);

				displayVector(vec);
				break;
			}
			case 5: {
				auto vec = Manager::getMultipleManagers();

				displayVector(vec);
				break;
			}
			}
			break;
		}

		case 4:
		{
			int id = stoi(input("Please enter Id of the Manager: ", idRegex));
			auto m = Manager::getManagerByID(id);

			clearDisplay();
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

			waitBeforeClear();
			break;
		}
		}	
	}	
}

void runDepartmentMenu(){
	auto choice{0};
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

				Department d;
				d.getUserInput();

				clearDisplay();
				if (d.save()) {
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
				auto d = Department::getDepartment(id);

				clearDisplay();
				if (d) {
					auto oldMid = d->getManagerId();
					d->getUserInputForUpdate();
					auto newMid = d->getManagerId();

					clearDisplay();
					if (oldMid != newMid) {
						if (auto m = Manager::getManagerByID(newMid); !m) {
							std::cout << "No Manager exists with this id, Please retry with valid manager id\n";
							waitBeforeClear();
							break;
						}
					}
					if (d->update()) {
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
						auto d = Department::getDepartment(stoi(queryField));
						
						clearDisplay();
						if (d.has_value()) {
							std::cout << "Department with id: " << queryField << "\n";
							d.value().display();
						}
						else {
							std::cout << "No Department exists with id: " + queryField + "\n";
						}
						waitBeforeClear();
						break;
					}
					case 2: {
						queryField = input("Please enter name: ");
						auto vec = Department::getMultipleDepartment("name", queryField);

						displayVector(vec);
						break;
					}
					case 3: {
						queryField = input("Please enter manager ID: ");
						auto vec = Department::getMultipleDepartment("Department.manager_id", queryField);

						displayVector(vec);
						break;
					}
					case 4: {
						auto vec = Department::getMultipleDepartment();

						displayVector(vec);
						break;
				}
				}

				break;
			}

			case 4:
			{	

				int id = stoi(input("Please enter Id of the Department: ", idRegex));
				auto d = Department::getDepartment(id);

				clearDisplay();
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

				waitBeforeClear();
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
					auto e = Salary::getSalaryByID(stoi(queryField));
					
					clearDisplay();
					if (e.has_value()) {
						std::cout << "Salary details of Employee with id: " << queryField << '\n';
						e.value().display();
					}
					else {
						std::cout << "No Employee exists with id" << queryField << '\n';
					}
					waitBeforeClear();
					break;
				}
				case 2: {
					queryField = input("Please enter fisrt name: ");
					auto vec = Salary::getMultipleSalary("firstname", queryField);
					displayVector(vec);
					break;
				}
				case 3: {
					queryField = input("Please enter last name: ");
					auto vec = Salary::getMultipleSalary("lastname", queryField);
					displayVector(vec);
					break;
				}
				case 4: {
					queryField = input("Please enter department name: ");
					auto vec = Salary::getMultipleSalary("department.name", queryField);
					displayVector(vec);
					break;
				}
				case 5: {
					auto vec = Salary::getMultipleSalary();
					displayVector(vec);
					break;
				}
			}
			break;
		}

		case 2:
		{
			auto id = stoi(input("Please enter id of the employee: ", idRegex));
			auto salary = Salary::getSalaryByID(id);

			if (salary.has_value()) {
				salary.value().getUserInputForUpdate();
				salary.value().update();
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

		choice = stoi(input("Please Select an Option: ",mainChoiceRegex));

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
			std::cout << "Thank You\n";
			break;
		default:
			std::cout << "Invalid choice\n";
			break;
		}

	}
}

int main()
{
	runMenu();
	return 0;
}
