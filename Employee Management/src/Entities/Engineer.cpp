#include "../../include/Entities/Engineer.h"

namespace Entity {

	std::optional<Engineer> Engineer::getEngineerById(int id) {
		auto dbI = DB::getDB();


		Engineer e;

		std::string selectQuery = "SELECT * FROM Employee JOIN Engineer ON Employee.id = Engineer.id WHERE Employee.id = " + std::to_string(id) + ";";

		auto callback = [](void* data, int argc, char** argv, char** azColName) {
			Engineer* emp = static_cast<Engineer*>(data);

			emp->setId(argv[0] ? std::stoi(argv[0]) : -1);
			emp->setFirstname(argv[1] ? argv[1] : "");
			emp->setLastname(argv[2] ? argv[2] : "");
			emp->setDob(argv[3] ? argv[3] : "");
			emp->setMobile(argv[4] ? argv[4] : "");
			emp->setEmail(argv[5] ? argv[5] : "");
			emp->setAddress(argv[6] ? argv[6] : "");
			emp->setGender(argv[7] ? stringToGender(argv[7]) : Gender::Other);
			emp->setDoj(argv[8] ? argv[8] : "");
			emp->setManagerId(argv[9] ? std::stoi(argv[9]) : -1);
			emp->setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);
			emp->setProgrammingLanguage(argv[12] ? argv[12] : "");
			emp->setSpecialization(argv[13] ? argv[13] : "");
			if (auto salary = Salary::getSalaryByID(emp->getId()); salary) {
				emp->setSalary(std::move(*salary));
			}
			return 0;
			};


		try {
			dbI->executeSelectQuery(selectQuery.c_str(), callback, &e, "Engineer selected with ID " + std::to_string(id) + ".");
		}
		catch (...) {
			return std::nullopt;
		}

		if (e.getId() != 0) {
			return e;
		}


		return std::nullopt;
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
			emp.setProgrammingLanguage(argv[12] ? argv[12] : "");
			emp.setSpecialization(argv[13] ? argv[13] : "");
			if (auto salary = Salary::getSalaryByID(emp.getId()); salary) {
				emp.setSalary(std::move(*salary));
			}


			vecOfEmp->push_back(std::move(emp));
			return 0;
			};


		try {
			dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfEmp, "Multiple Engineers selected.");
		}
		catch (...) {
			return {};
		}


		return vecOfEmp;
	}

	bool Engineer::save() const {
		auto dbI = DB::getDB();

		if (!Employee::save()) return false;

		std::string insertQuery = "INSERT INTO Engineer VALUES (" + std::to_string(getId()) + ",'" + programming_language + "', '" + specialization + "');";

		if (!dbI->executeQuery(insertQuery.c_str(), "An Engineer Inserted with ID : " + std::to_string(getId()) + ".")) { return false; }

		return true;
	}

	bool Engineer::update() const {
		auto dbI = DB::getDB();

		if (!Employee::update()) return false;

		std::string updateQuery = "UPDATE Engineer SET ";
		updateQuery +=
			"programming_language='" + programming_language +
			"', specialization='" + specialization +
			"' WHERE id = " + std::to_string(getId()) + ";";


		if (!dbI->executeQuery(updateQuery.c_str(), "Engineer Updated with ID: " + std::to_string(getId()) + ".")) return false;

		if (dbI->noOfRowChanged() == 0) return false;

		return true;
	}

	bool Engineer::deleteThis() const {
		return Employee::deleteThis();
	}

	bool Engineer::getUserInput() noexcept {
		if (!Employee::getUserInput()) return false;
		try {
			setProgrammingLanguage(inputWithQuit("Enter programming_language name: ", nonEmptyRegex));
			setSpecialization(inputWithQuit("Enter specialization: ", nonEmptyRegex));
			return true;
		}
		catch (...) {
			*this = Engineer();
			return false;
		}

	}

	bool Engineer::getUserInputForUpdate() noexcept {

		if (!Employee::getUserInputForUpdate()) return false;

		try {
			auto pl{ inputWithQuit("Enter Programming Language: ",nonEmptyRegex, true) };
			if (!(pl == "#")) setProgrammingLanguage(pl);

			auto sp{ inputWithQuit("Enter specialization: ", nonEmptyRegex , true) };
			if (!(sp == "#")) setSpecialization(sp);

			return true;
		}
		catch (...) {
			*this = Engineer();
			return false;
		}
	}

	void Engineer::display() const {
		Employee::display();
		std::cout << "| Prog. Language             | " << std::setw(48) << std::left << programming_language << " |" << std::endl;
		std::cout << "| Specialization             | " << std::setw(48) << std::left << specialization << " |" << std::endl;
		std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
	}

	const char* Engineer::getClassName() const {
		return "Eng";
	}

}