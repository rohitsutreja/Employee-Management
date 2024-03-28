#include "include/Controllers/SalaryController.h"
#include "include/Util.h"
#include "include/Entities/Salary.h"


using Entity::Salary;


namespace Controller {
	void viewSalaries() {
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
	void updateSalary() {
		auto id = stoi(input("Please enter id of the employee: ", idRegex));
		auto salary = Salary::getSalaryByID(id);

		if (salary) {
			if (salary->getUserInputForUpdate()) {
				std::cout << "Updation Cancelled\n";
				return;
			}
			if (salary->update()) {
				std::cout << getInGreen("Updation Successfull.") << '\n';
			}
			else {
				std::cout << getInRed("Updation Failed") << '\n';
			}
		}
		else {
			std::cout << "No Employee exists with id: " << id << '\n';
		}
	};
	void incrementSalary() {
		auto id = stoi(input("Please enter id of the employee: ", idRegex));
		auto salary = Salary::getSalaryByID(id);

		if (salary) {
			auto inc = input("Enter the % of increment (1 - 500): ", std::regex{ "\\b([1-9]|[1-9][0-9]|[1-4][0-9]{2}|500)\\b" });

			salary->increment(stoi(inc));

			clearDisplay();
			if (salary->update()) std::cout << getInGreen("Increment Successfull.") << '\n';
			else std::cout << getInRed("Increment Failed.") << '\n';
		}
		else {
			std::cout << "No employee exists with this id.\n";
		}

	}

}