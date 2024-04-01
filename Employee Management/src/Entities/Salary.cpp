#include "../../include/Entities/Salary.h"


namespace Entity {

	std::optional<Salary> Salary::getSalaryByID(int id) {
		auto dbI = DB::getDB();

		std::string selectQuery = "SELECT * FROM SALARY WHERE id = " + std::to_string(id) + ";";

		Salary salary;

		auto callback = [](void* data, int argc, char** argv, char** azColName) {

			Salary* s = static_cast<Salary*>(data);

			s->setID(argv[0] ? std::stoi(argv[0]) : -1);
			s->setBaseSalary(argv[2] ? std::stof(argv[2]) : 0.0);
			s->setBonus(argv[3] ? std::stof(argv[3]) : 0.0);

			return 0;
			};


		try {
			dbI->executeSelectQuery(selectQuery.c_str(), callback, &salary, "Salary selected for Employee with ID " + std::to_string(id) + ".");
		}
		catch (...) {
			return std::nullopt;
		}


		if (salary.getId() == 0) {
			return std::nullopt;
		}
		return salary;
	}

	std::vector<Salary> Salary::getMultipleSalary(const std::string& queryField, const std::string& queryValue) {
		auto dbI = DB::getDB();

		std::vector<Salary> vecOfSal;

		std::string selectQuery;


		if (queryField == "id" || queryField == "manager_id" || queryField == "department_id") {
			selectQuery = "SELECT Salary.* FROM Employee JOIN Department ON Employee.department_id = Department.id JOIN Salary ON Employee.id = Salary.id WHERE " + queryField + " = " + queryValue + " COLLATE NOCASE; ";
		}
		else if (queryField == "" && queryValue == "") {
			selectQuery = "SELECT Salary.* FROM Employee JOIN Department ON Employee.department_id = Department.id JOIN Salary ON Employee.id = Salary.id COLLATE NOCASE;";
		}
		else {
			selectQuery = "SELECT Salary.* FROM Employee JOIN Department ON Employee.department_id = Department.id JOIN Salary ON Employee.id = Salary.id WHERE " + queryField + " = '" + queryValue + "' COLLATE NOCASE;";
		}


		auto callback = [](void* data, int argc, char** argv, char** azColName) {
			std::vector<Salary>* vecOfSal = static_cast<std::vector<Salary>*>(data);

			Salary sal;

			sal.setID(std::stoi(argv[0]));
			sal.setBaseSalary(std::stof(argv[2]));
			sal.setBonus(std::stof(argv[3]));

			vecOfSal->push_back(std::move(sal));
			return 0;
			};


		try {
			dbI->executeSelectQuery(selectQuery.c_str(), callback, &vecOfSal, "Salary of Multiple Employee selected.");
		}
		catch (...) {
			return {};
		}



		return vecOfSal;
	}

	bool Salary::save() const {
		auto dbI = DB::getDB();

		std::string  insertQuery = "INSERT INTO Salary "
			"(id, base_salary, bonus) VALUES (";

		insertQuery += std::to_string(id) +
			", " + std::to_string(base_salary) +
			", " + std::to_string(bonus) +
			+");";

		if (!dbI->executeQuery(insertQuery.c_str(), "Salary for an Employee Inserted with ID: " + std::to_string(id) + ".")) { return false; }

		return true;
	}

	bool Salary::update() const {
		auto dbI = DB::getDB();

		std::string updateQuery = "UPDATE Salary SET ";
		updateQuery +=
			"base_salary= " + std::to_string(base_salary) +
			",bonus = " + std::to_string(bonus) +
			" WHERE id = " + std::to_string(id) + ";";


		if (!dbI->executeQuery(updateQuery.c_str(), "Salary Updated for EMployee with ID: " + std::to_string(id) + ".")) return false;
		if (dbI->noOfRowChanged() == 0) return false;
		return true;
	}

	bool Salary::deleteThis() const {
		auto dbI = DB::getDB();

		std::string deleteQuery = "DELETE FROM Salary WHERE id = ";
		deleteQuery += std::to_string(id);

		if (!dbI->executeQuery(deleteQuery.c_str(), "Salary deleted for Employee with ID: " + std::to_string(id) + ".")) { return false; }

		if (dbI->noOfRowChanged() == 0) return false;
		return true;
	}

	bool Salary::getUserInput() noexcept {
		try {
			setBaseSalary(stof(inputWithQuit("Please enter Base Salary: ", salaryRegex)));
			setBonus(stof(inputWithQuit("Please enter Bonus: ", salaryRegex)));
			//setAmount(base_salary + bonus);
			return true;
		}
		catch (...) {
			*this = Salary();
			return false;
		}
	}

	bool Salary::getUserInputForUpdate() noexcept {

		try {
			auto base = inputWithQuit("Please enter Base Salary: ", salaryRegex, true);
			if (base != "#") setBaseSalary(stof(base));

			auto bon = inputWithQuit("Please enter Bonus: ", salaryRegex, true);
			if (base != "#") setBonus(stof(bon));

			//setAmount(base_salary + bonus);

			return true;
		}
		catch (...) {
			*this = Salary();
			return false;
		}
	}

	void Salary::display() const {
		auto dbI = DB::getDB();

		std::string name = "";
		std::string selectQuery = "SELECT firstname, lastname FROM EMPLOYEE WHERE id = " + std::to_string(id) + ";";
		dbI->executeSelectQuery(selectQuery.c_str(), [](void* data, int argc, char** argv, char** aZcolname) {
			auto m = static_cast<std::string*>(data);

			*m += argv[0];
			*m += " ";
			*m += argv[1];

			return 0;
			}, &name, "Employee Selected to display salary.");

		std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
		std::cout << "|\033[32m ID\033[0m                         | " << std::setw(48) << std::left << id << " |" << std::endl;
		std::cout << "| Name                       | " << std::setw(48) << std::left << name << " |" << std::endl;
		std::cout << "| Base Salary                | " << std::setw(48) << std::left << base_salary << " |" << std::endl;
		std::cout << "| Bonus                      | " << std::setw(48) << std::left << bonus << " |" << std::endl;
		std::cout << "| Total Salary               | " << std::setw(48) << std::left << computeSalary() << " |" << std::endl;
		std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
	}

	void Salary::increment(int percentage) {
		base_salary = base_salary + (base_salary * percentage) / 100;
	}

	double Salary::computeSalary() const { return base_salary + bonus; }

}
