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
inline constexpr std::array<std::string_view, 5 > myTables = { "employee", "manager", "engineer", "salary", "department" };
inline constexpr std::array<std::string_view, 5> types = { "int","integer","varchar","float","date" };

class Table {

public:
	bool getUserInputForTable() {

		std::cout << "- Please enter ':q' at any point to cancel creation of table.\n\n";
	try{
		this->name = inputWithQuit("Enter the name of the table: ", nonEmptyRegex);
		std::cout << '\n';

		std::cout << "These are the supported types:\n";

		for (const auto& type : types) {
			std::cout << type << ', ';
		}
		std::cout << "\n";
		while (1) {
			auto fieldName = inputWithQuit("Enter the field name: ", nonEmptyRegex);
			auto fieldType = inputWithQuit("Enter the type of the field - " + fieldName + ": ", validTypes);

			keyType.insert({ fieldName,fieldType });

			auto choice = inputWithQuit("\nDo you want to add more fields (Y/N): ", yesNoRegex);

			if (choice == "n" || choice == "N") { break; }
			std::cout << "\n";
		}

		if (auto choice = inputWithQuit("\nDo you want to insert any foreign key field? (Y/N): ", yesNoRegex);  choice == "Y" || choice == "y") {
			while (1) {
				auto fieldName = inputWithQuit("Enter the field name: ", nonEmptyRegex);
				auto fieldType = inputWithQuit("Enter the type of the field - " + fieldName + ": ", validTypes);
				auto parentTable = inputWithQuit("Enter the name of the parent table: ", nonEmptyRegex);
				auto parentField = inputWithQuit("Enter the name of the parent field: ", nonEmptyRegex);

				std::cout << "\n";

				fKey.insert({ fieldName, {parentTable,parentField} });
				keyType.insert({ fieldName,fieldType });

				auto choice = inputWithQuit("\nDo you want to add more foreign keys? (Y/N): ", yesNoRegex);

				if (choice == "n" || choice == "N") { break; }
				std::cout << "\n";
			}
		}

		if (auto choice = inputWithQuit("\nDo you want to do on delete cascade? (Y/N): ", yesNoRegex); choice == "Y" || choice == "y") {
			onDeleteCascade = true;
		}

		keyType.insert({ "id", "int" });
	
		return true;
	}
	catch (...) {
		*this = Table();
		return false;
	}

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

		if(!dbI->executeQuery(query.c_str(), "Table Created: " + name)) return false;

		return true;
	};

	bool deleteThis() const {
		if (std::find(myTables.begin(), myTables.end(), toLower(name)) != myTables.end()) {
			MyLogger::info("Deletion failed", "- Trying to delete EMP DB table");
			return false;
		};

		std::string query = "DROP TABLE " + name + ";";

		auto dbI = DB::getDB();

		if (!dbI->executeQuery(query.c_str(),"Deleted Table: " + name)) return false;

		return true;
	};

	void display() const {
		std::cout << "+----------------------------+----------------------------------------+" << std::left << std::endl;
		for (auto& [key, type] : keyType) {
			std::cout << "| " << std::setw(27)  << key << "| " << std::setw(38)  << type << " |" << std::endl;
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
	    }, &t.keyType, "Selected Table: " + name);


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

			}, &tableList, "Selected Tables list");

		return tableList;
	}
	
	bool insertRecord() {
		std::cout << "- Enter ':q' at any point to cacncel insertion\n";
		std::cout << "- Enter '#' to keep value NULL\n\n";
		keyVal.clear();

		auto val = inputWithQuit("Enter id: ", idRegex);
		keyVal.insert({ "id" , val });

		for (const auto& [key, type] : keyType) {
			if (key == "id") continue;

			if (std::find(numericFields.begin(), numericFields.end(), toLower(type)) != numericFields.end()) {
				auto val = inputWithQuit("Enter " + key + ": ", realNumberRegex, true);
				keyVal.insert({ key,val });
			}
			else {
				auto val = inputWithQuit("Enter " + key + ": ", nonEmptyRegex , true);
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
			if (std::find(numericFields.begin(), numericFields.end(),toLower(keyType[key])) != numericFields.end()) {
				insertQuery = insertQuery + (val == "#" ?  "NULL" : val) + ",";
			}
			else {
				insertQuery = insertQuery + ((val == "#") ? ("NULL ,") : ("'" + val + "' ,"));
			}
			
		}

		insertQuery.erase(insertQuery.find_last_of(','), 1);

		insertQuery += ");";


		auto dbI = DB::getDB();
		if (dbI->executeQuery(insertQuery.c_str(), "Inserted Record in: " + name)) return true;

		return false;	
	}

	bool deleteRecord () const 
	{
		auto id = input("Enter id ('#' to cancel deletion): ", idRegex, true);

		if (id == "#") {
			return false;
		}

		std::string deleteQuery = "DELETE FROM " + name + " WHERE id = " + id;

		auto dbI = DB::getDB();

		if(dbI->executeQuery(deleteQuery.c_str(), "Deleted record from "+ name)) return true;

		return false;
	}

	bool updateRecord() {

		auto id = input("Enter id ('#' to cancel updation): ", idRegex,true);

		if (id == "#") {
			return false;
		}

		keyVal.clear();

		clearDisplay();
		std::cout << "\n- Enter '#' to keep values as it is.\n- Press ':q' at any point to quit the updation\n\n";

		for (auto& [key, type] : keyType) {
			if (key == "id") continue;

			if (std::find(numericFields.begin(), numericFields.end(), toLower(type)) != numericFields.end()) {
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

			if (std::find(numericFields.begin(), numericFields.end(), toLower(keyType[key])) != numericFields.end()) {
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

		if (dbI->executeQuery(updateQuery.c_str(), "Updated record in " + name)) return true;

		return false;
	}

	void displayFilteredRecords() {

		auto field = input("Enter the name of the field by which you want to filter: ", nonEmptyRegex);
		auto value = input("Enter the value of " + field + ": ");


		std::string selectQuery;

		if (std::find(numericFields.begin(), numericFields.end(), toLower(keyType[field])) != numericFields.end()) {
			selectQuery = "SELECT * FROM " + name + " WHERE " + field + " = " + value + " COLLATE NOCASE; ";
		}
		else {
			selectQuery = "SELECT * FROM " + name + " WHERE " + field + " = '" + value + "' COLLATE NOCASE; ";
		}
		auto dbI = DB::getDB();

	

		clearDisplay();

		int count = 0;
		bool succeed = dbI->executeSelectQuery(selectQuery.c_str(), [](void* data, int argc, char** argv, char** argZcolName) {
			auto count = static_cast<int*>(data);
			(*count)++;
			
			std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
			for (int i = 0; i < argc; i++) {
				
				std::cout << "| " << std::setw(27) << std::left << argZcolName[i] << "| " << std::setw(48) << std::left << argv[i] << " |" << std::endl;
			}
			std::cout << "+----------------------------+--------------------------------------------------+" << std::endl;
			std::cout << "\n\n";
		
			return 0;
			}, &count, "Selected Records from: " + name);

		std::cout << "--> " << count << " - Records found." << std::endl;

		if (!succeed) {
			clearDisplay();
			std::cout << "There is no '" << field << "' in the table " << name << '\n';
			return;
		}
	}

	void displayAllRecords() const {
		std::string selectQuery = "SELECT * FROM " + name + ";";

		auto dbI = DB::getDB();
		
		int count = 0;
		bool succeed = dbI->executeSelectQuery(selectQuery.c_str(), [](void* data, int argc, char** argv, char** argZcolName) {
			auto count = static_cast<int*>(data);
			(*count)++;
			std::cout << "+------------------+----------------------------------------+" << std::endl;
			for (int i = 0; i < argc; i++) {
				std::cout << "| " << std::setw(17) << std::left << argZcolName[i] << "| " << std::setw(38) << std::left << (argv[i] ? argv[i] : "NULL") << " |" << std::endl;
			}
			std::cout << "+------------------+----------------------------------------+" << std::endl;

			return 0;
		}, &count, "Selected Records from: "+ name);

		std::cout << "--> " << count << " - Records found." << std::endl;
	}

	const std::string& getName()  const {
		return name;
	}

private:
	std::string name;
	std::map<std::string, std::string> keyType;
	std::map<std::string, std::string> keyVal;
	std::map<std::string, std::pair<std::string, std::string>> fKey;
	bool onDeleteCascade = false;
};