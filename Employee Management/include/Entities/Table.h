#pragma once
#include <optional>
#include <string>
#include <map>
#include <iostream>
#include "../Util.h"
#include "../DB.h"

inline std::vector<std::string> myTables = { "Employee", "Manager", "Engineer", "Salary", "Department" };

class Table {

public:
	bool save(){
		std::string query = "";

		query += "CREATE TABLE IF NOT EXISTS " + name + " ("
			"id INTEGER PRIMARY KEY";

		for (auto& [key, type] : keyType) {
			auto str = ", " +  key + " " + type;
			query += str;
			
		}
		query += ")";
		std::cout << query;
		auto dbI = DB::getDB();

		if(!dbI->executeQuery(query.c_str())) return false;


		clearDisplay();


		std::cout << "table created successfully\n";
		return true;
	};

	void display() {
		std::cout << "+------------------+----------------------------------------+" << std::left << std::endl;
	
		for (auto& [key, type] : keyType) {
			std::cout << "| " << std::setw(17)  << key << "| " << std::setw(38)  << type << " |" << std::endl;
			//std::cout << key << " " << type << '\n';
		}

		std::cout << "+------------------+----------------------------------------+" << std::endl;
	}

	static std::optional<Table> getTable(std::string name) {
		std::string query = "PRAGMA table_info(" + name + ")";

		Table t;

		auto dbI = DB::getDB();

		dbI->executeSelectQuery(query.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		
			auto keyType = static_cast<std::map<std::string, std::string>*>(data);

			keyType->insert({argv[1],argv[2] ? argv[2] : "NULL"});

			return 0;
	    }, &t.keyType);


		if (t.keyType.size() == 0) return {};

		return t;

	}
	
	bool deleteThis() {
	
		if (std::find(myTables.begin(), myTables.end(), name) != myTables.end()) return false;

		std::string query = "DROP TABLE " + name + ";";

		auto dbI = DB::getDB();

		if (!dbI->executeQuery(query.c_str())) return false;

		return true;
	};
	
	void getUserInputForTable() {
		this->name = input("Enter the name of the table: ");
		std::cout << '\n';

		while (1) {
			auto fieldName = input("Enter the field name: ");
			auto fieldType = input("Enter the type of the field - " + fieldName + ": ");

			std::cout << "\n";

			keyType.insert({ fieldName,fieldType });

			auto choice = input("Do you want to add more fields (Y/N): ");

			if (choice == "n" || choice == "N") { break; }
			std::cout << "\n";
		}

	};


	void insertInto() {
		for (auto& [key, type] : keyType) {
			auto val = input("Enter " + key + ": ");
			keyVal.insert({ key,val });


		}
	}


  


private:
	std::string name;
	std::map<std::string, std::string> keyType;
	std::map<std::string, std::string> keyVal;
};