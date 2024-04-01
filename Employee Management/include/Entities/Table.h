#pragma once
#include <optional>
#include <string>
#include <array>
#include <map>
#include <iostream>
#include "../Util.h"
#include "../DB.h"
#include<filesystem>
#include <fstream>

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
	bool getUserInputForTable();

	bool save();

	bool deleteThis() const;

	void display() const;

	static std::optional<Table> getTable(std::string name);
	
	static std::vector<Table> getAllTables();
	
	bool insertRecord();

	bool deleteRecord() const;

	bool updateRecord();

	void displayFilteredRecords();

	void displayAllRecords() const;

	static bool writeCSV();

	static bool exportToCsv(const std::string_view& tableName, const std::filesystem::path& path);

	const std::string& getName()  const;


private:
	std::string name;
	std::map<std::string, std::string> keyType;
	std::map<std::string, std::string> keyVal;
	std::map<std::string, std::pair<std::string, std::string>> fKey;
	bool onDeleteCascade = false;
};

