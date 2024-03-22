#include "include/Util.h"
#include "include/Entities/Department.h"
#include "include/Entities/Manager.h"

void insertDepartment() {
	clearDisplay();

	Department department;

	if (!department.getUserInput()) {
		clearDisplay();
		std::cout << "Insertion cancelled\n";
		return;
	}


	if (auto duplicateDepartment = Department::getDepartmentById(department.getId()); duplicateDepartment) {
		std::cout << "This employee id already exists, Please try again with another id.\n";
		return;
	}

	if (department.save()) {
		std::cout << "Insertion Successfull.\n";
	}
	else {
		std::cout << "Insertion Failed.\n";
	};

};
void updateDepartment() {
	int id = stoi(input("Please enter Id of the Department: ", idRegex));
	auto department = Department::getDepartmentById(id);

	clearDisplay();
	if (department) {
		auto oldMid = department->getManagerId();

		if (!department->getUserInputForUpdate()) {
			clearDisplay();
			std::cout << "Updation cancelled\n";
			return;
		}

		auto newMid = department->getManagerId();

		clearDisplay();
		if (oldMid != newMid) {
			if (auto manager = Manager::getManagerById(newMid); !manager) {
				std::cout << "No Manager exists with this id, Please retry with valid manager id\n";
				return;
			}
		}
		if (department->update()) {
			std::cout << "Updation Successfull.\n";
		}
		else {
			std::cout << "Updation Failed.\n";
		}
	}
	else {
		std::cout << "No department exist with id: " << id << "\n";
	}

};
void deleteDepartment() {
	int id = stoi(input("Please enter Id of the Department: ", idRegex));
	auto department = Department::getDepartmentById(id);


	clearDisplay();
	if (department) {
		auto employyesInDepartment = Employee::getMultipleEmployee("department_id", std::to_string(department->getId()));
		if (employyesInDepartment.size() != 0) {
			std::cout << "There are total [" << employyesInDepartment.size() << "] employees in this department.\n\n";
			std::cout << "If you delete this department, they will be deleted too.\n\n";
			auto ip = input("Do you still want to delete it? ( Y / N ): ", std::regex{ "^[YNyn]$" });
			if (ip == "N" || ip == "n") {
				std::cout << "\nDeletion cancelled\n";
				return;
			}
			for (auto e : employyesInDepartment) {
				e.deleteThis();
			}
			if (department->deleteThis()) {
				std::cout << "\nDeletion Successfull.\n";
			}
			else {
				std::cout << "\nDeletion Failed.\n";
			}

		}
	}
	else {
		std::cout << "No department exist with id: " << id << "\n";
	}
}
void viewDepartments() {
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
		auto department = Department::getDepartmentById(stoi(queryField));

		clearDisplay();
		if (department) {
			std::cout << "Department with id: " << queryField << "\n";
			department->display();
		}
		else {
			std::cout << "No Department exists with id: " + queryField + "\n";
		}
		return;
	}
	case 2: {
		queryField = input("Please enter name: ");
		auto departmentVector = Department::getMultipleDepartment("name", queryField);
		displayVector(departmentVector);
		break;
	}
	case 3: {
		queryField = input("Please enter manager ID: ");
		auto departmentVector = Department::getMultipleDepartment("Department.manager_id", queryField);
		displayVector(departmentVector);
		break;
	}
	case 4: {
		auto departmentVector = Department::getMultipleDepartment();
		displayVector(departmentVector);
		break;
	}
	}
};