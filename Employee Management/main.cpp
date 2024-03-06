#include <iostream>
#include <stdlib.h>
#include "sqlite/sqlite3.h"
#include"include/Employee.h"
#include "include/DB.h"
#include "include/Regex.h"
#include "include/Department.h"



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
			e.display();
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
		Employee e = Employee::getEmployeeById(id);
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


	std::cout << "\n--------------------------------------------WELCOME--------------------------------------------\n";


	int choice{};
	while (1) {
		
		std::cout << "1. Employee Menu\n";
		std::cout << "2. Department Menu\n";
		std::cout << "3. Quit\n\n";

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
			std::cout << "Thank You\n";
			break;
		}
		else {
			std::cout << "Please choose valid option: ";
		}
	}








	return 0;
}
