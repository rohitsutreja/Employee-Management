#include <iostream>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include"include/Employee.h"
#include "include/DB.h"
#include "include/Regex.h"
#include "include/Department.h"
#include "include/Engineer.h"
#include "include/Manager.h"



void runEmployeeMenu() {
	auto choice{0};

	while (1) {
		std::cout << "1. Insert an Employee\n";
		std::cout << "2. Update an Employee\n";
		std::cout << "3. View an Employee\n";
		std::cout << "4. Delete an Employee\n";
		std::cout << "5. Main menu\n";

		choice = stoi(input("\nPlease select an option: "));

		std::cout << '\n';

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
			std::cout << "Please Enter a valid choice!\n";
			continue;
		}

		break;
	}
	system("CLS");
	switch (choice) {
	case 1:
	{
		Employee e;
		e.getUserInput();
		e.save();
		break;
	}

	case 2:
	{
		auto id = stoi(input("Please enter Id of the employee: ", idRegex));
		auto e = Employee::getEmployeeById(id);

		if (e.has_value()) {
			e.value().getUserInputForUpdate();
			e.value().update();
		}
		else {
			std::cout << "No Employee Exist with given ID\n";
		}
		
		break;
	}

	case 3:
	{	
		std::string queryField;
		auto choice{ 0 };

		while (1) {
			std::cout << "1. View by ID\n";
			std::cout << "2. View by first name\n";
			std::cout << "3. View by last name\n";
			std::cout << "4. View by Department\n";
			std::cout << "5. View All Employee\n\n";

			choice = stoi(input("Please Select an Option: "));

			std::cout << '\n';

			if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
				std::cout << "Please Enter a valid choice!\n";
				continue;
			}

			break;

			
		}

		system("CLS");
		switch (choice) {
		case 1: {
			queryField = input("Please enter ID: ", idRegex);
			auto e = Employee::getEmployeeById(stoi(queryField));
			std::cout << "Employee with id: " << queryField <<'\n';
			if (e.has_value()) {
				e.value().display();
			}
			else {
				std::cout << "No Employee Exist with given ID";
			}
			
			std::cout << '\n';
			break;
		}
		case 2: {
			queryField = input("Please enter fisrt name: ");
			auto vec = Employee::getMultipleEmployee("firstname", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 3: {
			queryField = input("Please enter last name: ");
			auto vec = Employee::getMultipleEmployee("lastname", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 4: {
			queryField = input("Please enter department name: ");
			auto vec = Employee::getMultipleEmployee("department.name", queryField);
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 5: {

			
			auto vec = Employee::getMultipleEmployee();
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		}

		break;
	}

	case 4:
	{
		int id = stoi(input("Please enter Id of the employee: ", idRegex));
		auto e = Employee::getEmployeeById(id);
		if (e.has_value()) {
			e.value().deleteThis();
			std::cout << "Employee Deleted\n";
		}
		else {
			std::cout << "No EMployee exist with this ID\n";
		}

	
		
		break;
	}

	case 5: {
		break;
	}
	}
}

void runEngineerMenu(){
	auto choice{ 0 };

	while (1) {
		std::cout << "1. Insert an Engineer\n";
		std::cout << "2. Update an Engineer\n";
		std::cout << "3. View an Engineer\n";
		std::cout << "4. Delete an Engineer\n";
		std::cout << "5. Main menu\n";

		choice = stoi(input("\nPlease select an option: "));

		std::cout << '\n';

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
			std::cout << "Please Enter a valid choice!\n";
			continue;
		}

		break;
	}
	system("CLS");
	switch (choice) {
	case 1:
	{
		Engineer e;
		e.getUserInput();
		e.save();
		break;
	}

	case 2:
	{
		auto id = stoi(input("Please enter Id of the engineer: ", idRegex));
		auto e = Engineer::getEngineerByID(id);
		e.getUserInputForUpdate();
		e.update();
		break;
	}

	case 3:
	{
		std::string queryField;
		auto choice{ 0 };

		while (1) {
			std::cout << "1. View by ID\n";
			std::cout << "2. View by first name\n";
			std::cout << "3. View by last name\n";
			std::cout << "4. View by Department\n";
			std::cout << "5. View All Engineers\n\n";
			std::cout << "6. View by Programming Language\n";

			choice = stoi(input("Please Select an Option: "));

			std::cout << '\n';

			if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice!=6) {
				std::cout << "Please Enter a valid choice!\n";
				continue;
			}

			break;


		}

		system("CLS");
		switch (choice) {
		case 1: {
			queryField = input("Please enter ID: ", idRegex);
			auto e = Engineer::getEngineerByID(stoi(queryField));
			std::cout << "Employee with id: " << queryField << '\n';
			e.display();
			std::cout << '\n';
			break;
		}
		case 2: {
			queryField = input("Please enter fisrt name: ");
			auto vec = Engineer::getMultipleEngineers("firstname", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 3: {
			queryField = input("Please enter last name: ");
			auto vec = Engineer::getMultipleEngineers("lastname", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 4: {
			queryField = input("Please enter department name: ");
			auto vec = Engineer::getMultipleEngineers("department.name", queryField);
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 5: {


			auto vec = Engineer::getMultipleEngineers();
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}

		case 6: {
			queryField = input("Please enter programming language: ");
			auto vec = Engineer::getMultipleEngineers("programming_language", queryField);
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		}

		break;
	}

	case 4:
	{
		int id = stoi(input("Please enter Id of the employee: ", idRegex));
		auto e = Engineer::getEngineerByID(id);
		e.deleteThis();
		break;
	}

	case 5: {
		break;
	}
	}
		
}

void runManagerMenu() {
	auto choice{ 0 };

	while (1) {
		std::cout << "1. Insert an Manager\n";
		std::cout << "2. Update an Manager\n";
		std::cout << "3. View an Manager\n";
		std::cout << "4. Delete an Manager\n";
		std::cout << "5. Main menu\n";

		choice = stoi(input("\nPlease select an option: "));

		std::cout << '\n';

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
			std::cout << "Please Enter a valid choice!\n";
			continue;
		}

		break;
	}
	system("CLS");
	switch (choice) {
	case 1:
	{
		Manager e;
		e.getUserInput();
		e.save();
		break;
	}

	case 2:
	{
		auto id = stoi(input("Please enter Id of the Manager: ", idRegex));
		auto e = Manager::getManagerByID(id);
		e.getUserInputForUpdate();
		e.update();
		break;
	}

	case 3:
	{
		std::string queryField;
		auto choice{ 0 };

		while (1) {
			std::cout << "1. View by ID\n";
			std::cout << "2. View by first name\n";
			std::cout << "3. View by last name\n";
			std::cout << "4. View by Department\n";
			std::cout << "5. View All Managers\n\n";


			choice = stoi(input("Please Select an Option: "));

			std::cout << '\n';

			if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) {
				std::cout << "Please Enter a valid choice!\n";
				continue;
			}

			break;


		}

		system("CLS");
		switch (choice) {
		case 1: {
			queryField = input("Please enter ID: ", idRegex);
			auto e = Manager::getManagerByID(stoi(queryField));
			std::cout << "Manager with id: " << queryField << '\n';
			e.display();
			std::cout << '\n';
			break;
		}
		case 2: {
			queryField = input("Please enter fisrt name: ");
			auto vec = Manager::getMultipleManagers("firstname", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 3: {
			queryField = input("Please enter last name: ");
			auto vec = Manager::getMultipleManagers("lastname", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 4: {
			queryField = input("Please enter department name: ");
			auto vec = Manager::getMultipleManagers("department.name", queryField);
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}
		case 5: {
			auto vec = Manager::getMultipleManagers();
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto e : vec) {
				e.display();
				std::cout << '\n';
			}
			break;
		}

		}

		break;
	}

	case 4:
	{
		int id = stoi(input("Please enter Id of the Manager: ", idRegex));
		auto e = Manager::getManagerByID(id);
		e.deleteThis();
		break;
	}

	case 5: {
		break;
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
		std::cout << "5. Main menu\n";

		choice = stoi(input("\nPlease select an option: "));

		std::cout << '\n';

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
			std::cout << "Please Enter a valid choice!\n";
			continue;
		}

		break;
	}
	system("CLS");
	switch (choice) {
	case 1:
	{
		Department d;
		d.getUserInput();
		d.save();
		break;
	}

	case 2:
	{
		int id = stoi(input("Please enter Id of the Department: ", idRegex));
		Department d = Department::getDepartment(id);
		d.getUserInputForUpdate();
		d.update();
		break;
	}

	case 3:
	{


		std::string queryField;
		auto choice{ 0 };

		while (1) {
			std::cout << "1. View by ID\n";
			std::cout << "2. View by name\n";
			std::cout << "3. View by manager ID\n";
			std::cout << "4. View All Departments\n\n";

			choice = stoi(input("Please Select an Option: "));

			std::cout << '\n';

			if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
				std::cout << "Please Enter a valid choice!\n";
				continue;
			}

			break;


		}

		system("CLS");
		switch (choice) {
		case 1: {
			queryField = input("Please enter ID: ", idRegex);
			auto d = Department::getDepartment(stoi(queryField));
			std::cout << "Department with id: " << queryField << '\n';
			d.display();
			std::cout << '\n';
			break;
		}
		case 2: {
			queryField = input("Please enter name: ");
			auto vec = Department::getMultipleDepartment("name", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto d : vec) {
				d.display();
				std::cout << '\n';
			}
			break;
		}
		case 3: {
			queryField = input("Please enter manager ID: ");
			auto vec = Department::getMultipleDepartment("Department.manager_id", queryField);

			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto d : vec) {
				d.display();
				std::cout << '\n';
			}
			break;
		}
		case 4: {


			auto vec = Department::getMultipleDepartment();
			std::cout << "<------------------- " << vec.size() << " - Records Found " << " -------------------->\n";
			for (auto d : vec) {
				d.display();
				std::cout << '\n';
			}
			break;
		}
		}

		break;


		//int id = stoi(input("Please enter Id of the Department: ", idRegex));
		//Department d = Department::getDepartment(id);
		//std::cout << '\n';
		//d.display();
		//std::cout << '\n';
		//break;
	}

	case 4:
	{
		int id = stoi(input("Please enter Id of the Department: ", idRegex));
		Department d = Department::getDepartment(id);
		d.deleteThis();
		break;
	}

	case 5: {
		break;
	}
	}
}



int main()
{


	std::cout << "\n<--------------------------------------------> EMPLOYEE MANAGEMENT SYSTEM <-------------------------------------------->\n";


	int choice{};
	while (1) {
		
		std::cout << "1. Employee Menu\n";
		std::cout << "2. Department Menu\n";
		std::cout << "3. Engineer Menu\n";
		std::cout << "4. Manager Menu\n";
		std::cout << "5. Quit\n\n";

		choice = stoi(input("Please Select an Option: "));

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
			std::cout << "Thank You\n";
			break;
		}
		else {
			std::cout << "Please choose valid option: ";
		}
	}


	//Engineer e = Engineer::getEngineerByID(14);

	//auto v = Engineer::getMultipleEngineers();

	//for (auto& e : v) {
	//	e.display();
	//}
	return 0;
}
