#include "../../include/Entities/Manager.h"

const char* Manager::getClassName() const {
	return "Manager";
}

bool Manager::getUserInputForUpdate() {

	if (!Employee::getUserInputForUpdate()) return false;

	try {
		auto me{ input("Enter Management Experience: ", oneOrTwoDigitRegex , true) };
		if (!(me == "#")) setManagementExperience(stoi(me));

		auto pt{ input("Enter Project Title: " , nonEmptyRegex , true) };
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
		setManagementExperience(stoi(input("Enter Management Experience years: ", oneOrTwoDigitRegex)));
		setProjectTitle(input("Enter Project Title: ", nonEmptyRegex));
		return true;
	}
	catch (...) {
		return false;
	}

}

void Manager::display() const {
	Employee::display();

	std::cout << "| Management Exp.  | " << std::setw(38) << std::left << (std::to_string(management_experience) + " years") << " |" << std::endl;
	std::cout << "| Project Title    | " << std::setw(38) << std::left << project_title << " |" << std::endl;
	std::cout << "+------------------+----------------------------------------+" << std::endl;
}

bool Manager::save() {
	auto dbI = DB::getDB();

	if(!Employee::save()) return false;

	std::string insertQuery = "INSERT INTO Manager VALUES (" + std::to_string(Employee::getId()) + "," + std::to_string(management_experience) + ", '" + project_title + "');";

	if (!dbI->executeQuery(insertQuery.c_str(), "Manager Inserted with ID : " + std::to_string(getId()) + ".")) { return false; }
	return true;
}

bool Manager::deleteThis() {
	auto dbI = DB::getDB();
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

		emp->setId(std::stoi(argv[0]));
		emp->setFirstname(argv[1]);
		emp->setLastname(argv[2]);
		emp->setDob(argv[3]);
		emp->setMobile(argv[4]);
		emp->setEmail(argv[5]);
		emp->setAddress(argv[6]);
		emp->setGender(stringToGender(argv[7]));
		emp->setDoj(argv[8]);
		if (argv[9]) {
			emp->setManagerId(std::stoi(argv[9]));
		}
		else {
			emp->setManagerId(-1);
		}
		emp->setDepartmentId(std::stoi(argv[10]));
		emp->setManagementExperience(std::stoi(argv[12]));
		emp->setProjectTitle(argv[13]);
		emp->setSalary(Salary::getSalaryByID(std::stoi(argv[0])).value());

		return 0;
		};

	dbI->executeSelectQuery(selectQuery.c_str(), callback, &m, "Engineer selected with ID " + std::to_string(id) + ".");

	if (m.getId() != 0) {
		return m;
	}

	return {};
}

std::vector<Manager> Manager::getMultipleManagers(const std::string& queryField, const std::string& queryValue) {
	auto dbI = DB::getDB();


	std::vector<Manager> vecOfEmp;

	std::string selectQuery;


	if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
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

		emp.setId(std::stoi(argv[0]));
		emp.setFirstname(argv[1]);
		emp.setLastname(argv[2]);
		emp.setDob(argv[3]);
		emp.setMobile(argv[4]);
		emp.setEmail(argv[5]);
		emp.setAddress(argv[6]);
		emp.setGender(stringToGender(argv[7]));
		emp.setDoj(argv[8]);
		if (argv[9]) {
			emp.setManagerId(std::stoi(argv[9]));
		}
		else {
			emp.setManagerId(-1);
		}
		emp.setDepartmentId(std::stoi(argv[10]));
		emp.setManagementExperience(std::stoi(argv[12]));
		emp.setProjectTitle(argv[13]);
		emp.setSalary(Salary::getSalaryByID(std::stoi(argv[0])).value());

		vecOfEmp->push_back(std::move(emp));
		return 0;
		};

	dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "Multiple Managers salected.");

	return vecOfEmp;
}

