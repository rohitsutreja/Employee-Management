#include "../include/Engineer.h"

const char* Engineer::getClassName() const {
	return "Eng";
}

void Engineer::getUserInputForUpdate() {

	Employee::getUserInputForUpdate();

	auto pl{ input("Enter Programming Language: ",nonEmptyRegex, true) };
	if (!(pl == "#")) setProgrammingLanguage(pl);

	auto sp{ input("Enter specialization: ", nonEmptyRegex , true) };
	if (!(sp == "#")) setSpecialization(sp);

}

void Engineer::getUserInput() {
	Employee::getUserInput();
	setProgrammingLanguage(input("Enter programming_language name: ", nonEmptyRegex));
	setSpecialization(input("Enter specialization: ", nonEmptyRegex));
}

void Engineer::display() const {
	Employee::display();

	std::cout << "| Prog. Language   | " << std::setw(38) << std::left << programming_language << " |" << std::endl;
	std::cout << "| Specialization   | " << std::setw(38) << std::left << specialization << " |" << std::endl;
	std::cout << "+------------------+----------------------------------------+" << std::endl;
}

bool Engineer::save() {
	auto dbI = DB::getDB();

	Employee::save();

	std::string insertQuery = "INSERT INTO Engineer VALUES (" + std::to_string(getId()) + ",'" + programming_language + "', '" + specialization + "');";

	if (!dbI->executeQuery(insertQuery.c_str(), "An Engineer Inserted with ID : " + std::to_string(getId()) + ".")) { return false; }
	return true;
}

bool Engineer::deleteThis() {
	auto dbI = DB::getDB();
	return  Employee::deleteThis();
}

bool Engineer::update() {
	auto dbI = DB::getDB();

	Employee::update();

	std::string updateQuery = "UPDATE Engineer SET ";
	updateQuery +=
		"programming_language='" + programming_language +
		"', specialization='" + specialization +
		"' WHERE id = " + std::to_string(getId()) + ";";


	if (!dbI->executeQuery(updateQuery.c_str(), "Engineer Updated with ID: " + std::to_string(getId()) + ".")) return false;

	return true;
}

std::optional<Engineer> Engineer::getEngineerById(int id) {
	auto dbI = DB::getDB();


	Engineer e;

	std::string selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id WHERE Employee.id = " + std::to_string(id) + ";";

	auto callback = [](void* data, int argc, char** argv, char** azColName) {
		Engineer* emp = static_cast<Engineer*>(data);

		emp->setId(std::stoi(argv[0]));
		emp->setFirstname(argv[1]);
		emp->setLastname(argv[2]);
		emp->setDob(argv[3]);
		emp->setMobile(argv[4]);
		emp->setEmail(argv[5]);
		emp->setAddress(argv[6]);
		emp->setGender(stringToGender(argv[7]));
		emp->setDoj(argv[8]);
		emp->setManagerId(std::stoi(argv[9]));
		emp->setDepartmentId(std::stoi(argv[10]));
		emp->setProgrammingLanguage(argv[12]);
		emp->setSpecialization(argv[13]);
		emp->setSalary(Salary::getSalaryByID(std::stoi(argv[0])).value());

		return 0;
		};

	dbI->executeSelectQuery(selectQuery.c_str(), callback, &e, "Engineer selected with ID " + std::to_string(id) + ".");

	if (e.getId() != 0) {

		return e;
	}


	return {};
}

std::vector<Engineer> Engineer::getMultipleEngineers(const std::string& queryField, const std::string& queryValue) {
	auto dbI = DB::getDB();


	std::vector<Engineer> vecOfEmp;

	std::string selectQuery;


	if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
		selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = " + queryValue + "; ";

	}
	else if (queryField == "" && queryValue == "") {
		selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id JOIN Department ON Employee.department_id = Department.id ;";
	}
	else {
		selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id JOIN Department ON Employee.department_id = Department.id WHERE " + queryField + " = '" + queryValue + "';";
	}


	auto callback = [](void* data, int argc, char** argv, char** azColName) {
		std::vector<Engineer>* vecOfEmp = static_cast<std::vector<Engineer>*>(data);

		Engineer emp;

		emp.setId(std::stoi(argv[0]));
		emp.setFirstname(argv[1]);
		emp.setLastname(argv[2]);
		emp.setDob(argv[3]);
		emp.setMobile(argv[4]);
		emp.setEmail(argv[5]);
		emp.setAddress(argv[6]);
		emp.setGender(stringToGender(argv[7]));
		emp.setDoj(argv[8]);
		emp.setManagerId(std::stoi(argv[9]));
		emp.setDepartmentId(std::stoi(argv[10]));
		emp.setProgrammingLanguage(argv[12]);
		emp.setSpecialization(argv[13]);

		emp.setSalary(Salary::getSalaryByID(std::stoi(argv[0])).value());

		vecOfEmp->push_back(std::move(emp));
		return 0;
		};

	dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "Multiple Engineers salected.");

	return vecOfEmp;
}
