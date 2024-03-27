#pragma once
#include <optional>
#include <string>
#include <array>
#include <map>
#include <iostream>
#include "../Util.h"
#include "../DB.h"


inline std::string toLower(std::string_view str) {
	std::string result;

	for (const auto& c : str) {
		result += tolower(c);
	}

	return result;
}
inline constexpr std::array<std::string_view, 3 > numericFields{ "int", "integer", "float" };
inline constexpr std::array<std::string_view, 5 > myTables = { "Employee", "Manager", "Engineer", "Salary", "Department" };

class Table {

public:
	void getUserInputForTable() {
		this->name = input("Enter the name of the table: ",nonEmptyRegex);
		std::cout << '\n';

		while (1) {
			auto fieldName = input("Enter the field name: ", nonEmptyRegex);
			auto fieldType = input("Enter the type of the field - " + fieldName + ": ", validTypes);

			
			keyType.insert({ fieldName,fieldType });

			auto choice = input("\nDo you want to add more fields (Y/N): ", yesNoRegex);

			if (choice == "n" || choice == "N") { break; }
			std::cout << "\n";
		}


		

		if (auto choice = input("\nDo you want to insert any foreign key field? (Y/N): " ,yesNoRegex);  choice == "Y" || choice == "y") {
			while (1) {
				auto fieldName = input("Enter the field name: ", nonEmptyRegex);
				auto fieldType = input("Enter the type of the field - " + fieldName + ": ",validTypes);
				auto parentTable = input("Enter the name of the parent table: ", nonEmptyRegex);
				auto parentField = input("Enter the name of the parent field: ",nonEmptyRegex);



				std::cout << "\n";

				fKey.insert({ fieldName, {parentTable,parentField} });
				keyType.insert({ fieldName,fieldType });

				auto choice = input("\nDo you want to add more foreign keys? (Y/N): ",yesNoRegex);

				if (choice == "n" || choice == "N") { break; }
				std::cout << "\n";
			}
		}

	

		if (auto choice = input("\nDo you want to do on delete cascade? (Y/N): ",yesNoRegex); choice == "Y" || choice == "y") {
			onDeleteCascade = true;
		}

		keyType.insert({ "id", "int" });

	};

	bool save(){
		std::string query = "";

		query += "CREATE TABLE IF NOT EXISTS " + name + " ("
			"id int PRIMARY KEY";

		for (auto& [key, type] : keyType) {
			if (key == "id") continue;
			auto str = ", " +  key + " " + type;
			query += str;
			
		}

		for (auto& [fKey, parent] : fKey) {
			query += (", FOREIGN KEY (" + fKey + ") REFERENCES " + parent.first + "(" + parent.second + ")");
		}

		if (onDeleteCascade) {
			query += " ON DELETE CASCADE);";
		}
		else {
			query += ");";
		}

		auto dbI = DB::getDB();

		if(!dbI->executeQuery(query.c_str())) return false;

		return true;
	};

	bool deleteThis() const {

		if (std::find(myTables.begin(), myTables.end(), name) != myTables.end()) return false;

		std::string query = "DROP TABLE " + name + ";";

		auto dbI = DB::getDB();

		if (!dbI->executeQuery(query.c_str())) return false;

		return true;
	};

	void displayThis() const {
		std::cout << "+----------------------------+----------------------------------------+" << std::left << std::endl;
	
		for (auto& [key, type] : keyType) {
			std::cout << "| " << std::setw(27)  << key << "| " << std::setw(38)  << type << " |" << std::endl;
			//std::cout << key << " " << type << '\n';
		}

		std::cout << "+----------------------------+----------------------------------------+" << std::endl;
	}

	static std::optional<Table> getTable(std::string name) {

		std::string query = "PRAGMA table_info(" + name + ")";

		Table t;

		t.name = name;

		auto dbI = DB::getDB();

		dbI->executeSelectQuery(query.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		
			auto keyType = static_cast<std::map<std::string, std::string>*>(data);

			keyType->insert({argv[1],argv[2] ? toLower(argv[2]) : "NULL"});

			return 0;
	    }, &t.keyType);


		if (t.keyType.size() == 0) return {};

		return t;

	}
	
	static std::vector<Table> getAllTables() {
		std::vector<Table> tableList;

		auto dbI = DB::getDB();

		dbI->executeSelectQuery("SELECT name FROM sqlite_master WHERE type = 'table'", [](void* data, int argc, char** argv, char** argZcol) {
			auto tableList = static_cast<std::vector<Table>*>(data);

			auto t = getTable(argv[0]);

			if (t) {
				tableList->push_back(std::move(*t));
			}

			return 0;

			}, &tableList, "");

		return tableList;
	}
	
	bool insertRecord() {
		
		keyVal.clear();

		auto val = input("Enter id: ", idRegex);
		keyVal.insert({ "id" , val });

		for (const auto& [key, type] : keyType) {
			if (key == "id") continue;

			if (std::find(numericFields.begin(), numericFields.end(), type) != numericFields.end()) {	
				auto val = input("Enter " + key + ": ", realNumberRegex, true);
				keyVal.insert({ key,val });
			}
			else {
				auto val = input("Enter " + key + ": ", nonEmptyRegex , true);
				keyVal.insert({ key,val });
			}
		}
	
		std::string insertQuery = "INSERT INTO " + name + "(";
			
		for (const auto& [key, val] : keyVal) {
				insertQuery = insertQuery + key + ",";
		}

		insertQuery.erase(insertQuery.find_last_of(','),1);

		insertQuery += ") VALUES (";

		for (auto& [key, val] : keyVal) {
			if (std::find(numericFields.begin(), numericFields.end(), keyType[key]) != numericFields.end()) {
				insertQuery = insertQuery + (val == "#" ?  "NULL" :val) + ",";
			}
			else {
				insertQuery = insertQuery + ((val == "#") ? ("NULL ,") : ("'" + val + "' ,"));
			}
			
		}

		insertQuery.erase(insertQuery.find_last_of(','), 1);

		insertQuery += ");";


		auto dbI = DB::getDB();
		if (dbI->executeQuery(insertQuery.c_str(), "")) return true;

		return false;	
	}

	bool deleteRecord () const {
		auto id = input("Enter id: ", idRegex);

		std::string deleteQuery = "DELETE FROM " + name + " WHERE id = " + id;

		auto dbI = DB::getDB();

		if(dbI->executeQuery(deleteQuery.c_str(), "")) return true;

		return false;
	}

	bool updateRecord() {
		auto id = input("Enter id: ", idRegex);

		keyVal.clear();

		std::cout << "\n- Enter '#' to keep values as it is.\n- Press ':q' at any point to quit the updation\n\n";

		for (auto& [key, type] : keyType) {
			if (key == "id") continue;

			if (std::find(numericFields.begin(), numericFields.end(), type) != numericFields.end()) {
				auto val = input("Enter " + key + ": ", realNumberRegex, true);
				if (val == "#") continue;
				keyVal.insert({ key,val });
			}
			else {
				auto val = input("Enter " + key + ": ", {}, true);
				if (val == "#") continue;
				keyVal.insert({ key,val });
			}
		}


		keyVal.insert({ "id", id});

		std::string updateQuery = "UPDATE " + name + " SET "; 

		for (auto& [key, val] : keyVal) {

			if (std::find(numericFields.begin(), numericFields.end(), keyType[key]) != numericFields.end()) {
				if (key == "id") continue;
				updateQuery += (key + "=" + val + ",");
			}
			else {
				updateQuery += (key + "= '" + val + "' ,");
			}
		}
		updateQuery.erase(updateQuery.find_last_of(','), 1);
		updateQuery += "WHERE id = " + id + ";";

		auto dbI = DB::getDB();

		std::cout << updateQuery;

		if (dbI->executeQuery(updateQuery.c_str(), "")) return true;

		return false;
	}

	void displayRecordsByField(const std::string& field, const std::string& value ) {
		std::string selectQuery;

		if (std::find(numericFields.begin(), numericFields.end(), keyType[field]) != numericFields.end()) {
			selectQuery = "SELECT * FROM " + name + " WHERE " + field + " = " + value + "; ";
		}
		else {
			selectQuery = "SELECT * FROM " + name + " WHERE " + field + " = '" + value + "'; ";
		}
		auto dbI = DB::getDB();

		dbI->executeSelectQuery(selectQuery.c_str(), [](void*, int argc, char** argv, char** argZcolName) {

			std::cout << "+------------------+----------------------------------------+" << std::endl;
			for (int i = 0; i < argc; i++) {
				std::cout << "| " << std::setw(17) << std::left << argZcolName[i] << "| " << std::setw(38) << std::left << argv[i] << " |" << std::endl;
			}
			std::cout << "+------------------+----------------------------------------+" << std::endl;
			return 0;
			}, nullptr, "");

	}

	void displayAllRecords() const {
		std::string selectQuery = "SELECT * FROM " + name + ";";

		auto dbI = DB::getDB();

		dbI->executeSelectQuery(selectQuery.c_str(), [](void*, int argc, char** argv, char** argZcolName) {
			std::cout << "+------------------+----------------------------------------+" << std::endl;
			for (int i = 0; i < argc; i++) {
				std::cout << "| " << std::setw(17) << std::left << argZcolName[i] << "| " << std::setw(38) << std::left << (argv[i] ? argv[i] : "NULL") << " |" << std::endl;
			}
			std::cout << "+------------------+----------------------------------------+" << std::endl;

			return 0;
		}, nullptr, "");


	}

	const std::string& getName() {
		return name;
	}

private:
	std::string name;
	std::map<std::string, std::string> keyType;
	std::map<std::string, std::string> keyVal;
	std::map<std::string, std::pair<std::string, std::string>> fKey;
	bool onDeleteCascade = false;
};