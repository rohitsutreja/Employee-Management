#ifndef UTIL_H
#define UTIL_H

#include<string>
#include <iostream>
#include <regex>
#include <chrono>
#include "Regex.h"
#include <optional>

namespace std {
	_EXPORT_STD _NODISCARD inline string to_string(const string& s) {
		return s;
	}
}

inline void clearDisplay() {
	system("CLS");
}

inline void waitBeforeClear() {
	std::cout << "\nPress Enter to continue...";
	std::string line;
	 std::getline(std::cin, line);

}

template<typename T>
void displayVector(const std::vector<T>& coll) {
	clearDisplay();
	std::cout << "<------------------- " << coll.size() << " - Records Found " << " -------------------->\n";
	for (const auto& e : coll) {
		e.display();
		std::cout << '\n';
	}
}

inline void displayCRUDMenu(std::string_view entity) {
	clearDisplay();
	std::cout << "1. Insert an " << entity << "\n";
	std::cout << "2. Update an " << entity << "\n";
	std::cout << "3. View " << entity << "\n";
	std::cout << "4. Delete an " << entity << "\n";
	std::cout << "5. Main menu\n";
}


inline void displayMainMenu() {
	clearDisplay();
	std::cout << "\n<--------------------------------------------> EMPLOYEE MANAGEMENT SYSTEM <-------------------------------------------->\n";
	std::cout << "\n1. Employee Menu\n";
	std::cout << "2. Department Menu\n";
	std::cout << "3. Engineer Menu\n";
	std::cout << "4. Manager Menu\n";
	std::cout << "5. Salary Menu\n";
	std::cout << "6. Quit\n\n";
}


inline std::string getLogTimeString() {
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
	std::tm currentTime;
	localtime_s(&currentTime, &time);
	char date_buffer[26];
	std::strftime(date_buffer, sizeof(date_buffer), "%d/%m/%y %H:%M:%S", &currentTime);

	return date_buffer;
}



inline std::string input(std::string_view prompt, std::optional<std::regex> r = universalRegex, bool allowSkip = false) {
	
	std::string ip;

	while (1) {
		std::cout << prompt;

		std::getline(std::cin, ip);

		if (allowSkip && ip == "#") {
			return "#"; 
		}

		if(std::regex_match(ip, r.value_or(universalRegex))) {
			return ip;
		}
		
		std::cout << "\033[31mInValid Input!!\033[0m\n";
	}
}


std::string inline getString() { return ""; };

template <typename T, typename... Types>
std::string getString(const T& first, Types&... args)
{
	std::string result{ "" };
	result = result + (first);
	result += getString(args...);

	return result;
}



#endif












