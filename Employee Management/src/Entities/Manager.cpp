#include "../../include/Entities/Manager.h"

const char* Manager::getClassName() const {
	return "Manager";
}

bool Manager::getUserInputForUpdate() {

	if (!Employee::getUserInputForUpdate()) return false;

	try {
		auto me{ inputWithQuit("Enter Management Experience: ", oneOrTwoDigitRegex , true) };
		if (!(me == "#")) setManagementExperience(stoi(me));

		auto pt{ inputWithQuit("Enter Project Title: " , nonEmptyRegex , true) };
		if (!(pt == "#")) setProjectTitle(pt);

		return true;
	}
	catch (...) {
		return false;
	}

	
}

bool Manager::getUserInput() {

	if (!Employee::getUserInput()) return false;

	try{
		setManagementExperience(stoi(inputWithQuit("Enter Management Experience years: ", oneOrTwoDigitRegex)));
		setProjectTitle(inputWithQuit("Enter Project Title: ", nonEmptyRegex));
		return true;
	}
	catch (...) {
		return false;
	}

}

void Manager::display() const {
	Employee::display();

	std::cout << "| Management Exp.            | " << std::setw(48) << std::left << (std::to_string(management_experience) + " years") << " |" << std::endl;
	std::cout << "| Project Title              | " << std::setw(48) << std::left << project_title << " |" << std::endl;
	std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
}

bool Manager::save() {
	auto dbI = DB::getDB();

	if(!Employee::save()) return false;

	std::string insertQuery = "INSERT INTO Manager VALUES (" + std::to_string(Employee::getId()) + "," + std::to_string(management_experience) + ", '" + project_title + "');";

	if (!dbI->executeQuery(insertQuery.c_str(), "Manager Inserted with ID : " + std::to_string(getId()) + ".")) { return false; }
	return true;
}

bool Manager::deleteThis() { 
	return Employee::deleteThis();
}

bool Manager::update() {
	auto dbI = DB::getDB();


	if (!Employee::update()) return false;;

	std::string updateQuery = "UPDATE Manager SET ";
	updateQuery +=
		"management_experience=" + std::to_string(management_experience) +
		", project_title='" + project_title +
		"' WHERE id = " + std::to_string(getId()) + ";";


	if (!dbI->executeQuery(updateQuery.c_str(), "Manager Updated with ID: " + std::to_string(getId()) + ".")) return false;

	if (dbI->noOfRowChanged() == 0) return false;

	return true;
}

std::optional<Manager> Manager::getManagerById(int id) {
	auto dbI = DB::getDB();

	Manager m;

	std::string selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id WHERE Employee.id = " + std::to_string(id) + ";";

	auto callback = [](void* data, int argc, char** argv, char** azColName) {
		Manager* emp = static_cast<Manager*>(data);

		emp->setId(argv[0] ? std::stoi(argv[0]) : -1);
		emp->setFirstname(argv[1] ? argv[1] : "");
		emp->setLastname(argv[2] ? argv[2] : "");
		emp->setDob(argv[3] ? argv[3] : "");
		emp->setMobile(argv[4] ? argv[4] : "");
		emp->setEmail(argv[5] ? argv[5] : "");
		emp->setAddress(argv[6] ? argv[6] : "");
		emp->setGender(argv[7]? stringToGender(argv[7]): Gender::Other);
		emp->setDoj(argv[8] ? argv[8] : "");
		emp->setManagerId(argv[9] ? std::stoi(argv[9]) : -1);
		emp->setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);
		emp->setManagementExperience(argv[12] ? std::stoi(argv[12]) : 0);
		emp->setProjectTitle(argv[13] ? argv[13] : "");
		
		if (auto salary = Salary::getSalaryByID(emp->getId()); salary) {
			emp->setSalary(std::move(*salary));
		}
		return 0;
		};


	try {
		dbI->executeSelectQuery(selectQuery.c_str(), callback, &m, "Manager selected with ID " + std::to_string(id) + ".");
	}
	catch (...) {
		return std::nullopt;
	}
	

	if (m.getId() != 0) {
		return m;
	}

	return std::nullopt;
}

std::vector<Manager> Manager::getMultipleManagers(const std::string& queryField, const std::string& queryValue) {
	auto dbI = DB::getDB();


	std::vector<Manager> vecOfEmp{};

	std::string selectQuery;


	if (queryField == "id" || queryField == "manager_id" || queryField == "department_id" || queryField == "management_experience") {
		selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = " + queryValue + "; ";

	}
	else if (queryField == "" && queryValue == "") {
		selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id JOIN Department ON Employee.department_id = Department.id ;";
	}
	else {
		selectQuery = "SELECT * FROM Employee JOIN Manager ON Employee.id = Manager.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = '" + queryValue + "';";
	}


	auto callback = [](void* data, int argc, char** argv, char** azColName) {
		std::vector<Manager>* vecOfEmp = static_cast<std::vector<Manager>*>(data);
		
		Manager emp;

		emp.setId(argv[0] ? std::stoi(argv[0]) : -1);
		emp.setFirstname(argv[1] ? argv[1] : "");
		emp.setLastname(argv[2] ? argv[2] : "");
		emp.setDob(argv[3] ? argv[3] : "");
		emp.setMobile(argv[4] ? argv[4] : "");
		emp.setEmail(argv[5] ? argv[5] : "");
		emp.setAddress(argv[6] ? argv[6] : "");
		emp.setGender(argv[7] ? stringToGender(argv[7]) : Gender::Other);
		emp.setDoj(argv[8] ? argv[8] : "");
		emp.setManagerId(argv[9] ? std::stoi(argv[9]) : -1);
		emp.setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);
		emp.setManagementExperience(argv[12] ? std::stoi(argv[12]) : 0);
		emp.setProjectTitle(argv[13] ? argv[13] : "");

		if (auto salary = Salary::getSalaryByID(emp.getId()); salary) {
			emp.setSalary(std::move(*salary));
		}

		vecOfEmp->push_back(std::move(emp));
		return 0;
	};

	try {
		dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "Multiple Managers selected.");
	}
	catch (...) {
		return {};
	}
	
	return vecOfEmp;
}

