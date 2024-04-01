
#include "include/Util.h"
#include "include/Entities/Engineer.h"
#include "include/Entities/Manager.h"


using Entity::Engineer;
using Entity::Manager;
using Entity::Employee;
using Entity::Department;


namespace Controller {
	void insertEngineer() {
		clearDisplay();

		Engineer engineer;

		if (!engineer.populateForInsertion())
		{
			clearDisplay();
			std::cout << "- Insertion cancelled\n";
			return;
		}

		clearDisplay();
		if (auto duplicateEngineer = Employee::getEmployeeById(engineer.getId()); duplicateEngineer) {
			std::cout << getInCyan("- This employee id already exist")<< ", Please try again with another id.\n";
			return;
		}

		if (auto department = Department::getDepartmentById(engineer.getDepartmentId()); !department) {
			std::cout << getInCyan("- This department does not exist") << ", Please try again with valid department id.\n";
			return;
		}

		if (auto manager = Manager::getManagerById(engineer.getManagerId()); engineer.getManagerId() != -1 && !manager) {
			std::cout << getInCyan("- This manager does not exist") << ", Please try again with valid manager id or skip it.\n";
			return;
		}
		
		if (engineer.save()) {
			std::cout << getInGreen("- Insertion successful.") << '\n';
		}
		else {
			std::cout << getInRed("- Insertion failed.") << '\n';
		};
		
	};

	void updateEngineer() {
		auto id = input("- Please enter id of the engineer (Enter '#' to cancel updation): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Updation cancelled.\n");
			return;
		}

		
		auto engineer = Engineer::getEngineerById(stoi(id));

		if (engineer) {
			auto oldMid = engineer->getManagerId();
			auto oldDid = engineer->getDepartmentId();

			if (!engineer->populateForUpdation()) {
				clearDisplay();
				std::cout << getInCyan("- Updation cancelled.\n");
				return;
			}

			clearDisplay();

			auto newMid = engineer->getManagerId();
			auto newDid = engineer->getDepartmentId();

			if (oldDid != newDid) {
				if (auto department = Department::getDepartmentById(newDid); !department) {
					std::cout << getInCyan("- This department does not exist") << ", Please try again with valid department id.\n";
					return;
				}
			}

			if (oldMid != newMid) {
				if (auto manager = Manager::getManagerById(newMid); !manager) {
					std::cout << getInCyan("- This manager does not exist") << ", Please try again with valid manager id.\n";
					return;
				}
			}

			if (engineer->update()) {
				std::cout << getInGreen("- Updation successful.") << '\n';
			}
			else {
				std::cout << getInRed("- Updation failed.") << '\n';
			}
		}
		else {
			std::cout << getInCyan("- No engineer exist with id: ") << id << "\n";
		}
	};

	void deleteEngineer() {
		auto id = input("- Please enter id of the engineer (Enter '#' to cancel deletion): ", idRegex, true);
		if (id == "#") {
			clearDisplay();
			std::cout << getInCyan("- Deletion cancelled.\n");
			return;
		}
		
		auto engineer = Engineer::getEngineerById(stoi(id));

		clearDisplay();
		if (engineer) {
			if (engineer->deleteThis()) {
				std::cout << getInGreen("- Deletion successful.") << '\n';
			}
			else {
				std::cout << getInGreen("- Deletion failed.") << '\n';
			}

		}
		else {
			std::cout << getInCyan("- No engineer exist with id: ") << id << "\n";
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

			queryField = input("- Please enter id: ", idRegex);
			auto engineer = Engineer::getEngineerById(stoi(queryField));

			clearDisplay();
			if (engineer) {
				std::cout << "- Engineer with id: " << getInGreen(queryField) << '\n';
				engineer->display();
			}
			else {
				std::cout << "- No engineer exist with id: " << queryField << "\n";
			}

			return;
		}
		case 2: {
			queryField = input("- Please enter fisrt name: ");
			auto engineersVector = Engineer::getMultipleEngineers("firstname", queryField);
			displayVector(engineersVector);
			break;
		}
		case 3: {
			queryField = input("- Please enter last name: ");
			auto engineersVector = Engineer::getMultipleEngineers("lastname", queryField);
			displayVector(engineersVector);
			break;
		}
		case 4: {
			queryField = input("- Please enter department name: ");
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
			queryField = input("- Please enter programming language: ");
			auto engineersVector = Engineer::getMultipleEngineers("programming_language", queryField);
			displayVector(engineersVector);
			break;
		}
		}
	};
}