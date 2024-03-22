
#include "include/Util.h"
#include "include/Entities/Engineer.h"
#include "include/Entities/Manager.h"

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