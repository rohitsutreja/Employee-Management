#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <regex>
#include <chrono>
#include <optional>

inline std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
inline std::regex mobileRegex(R"([0-9]{10})");
inline std::regex dateRegex(R"([0-3][0-9]-[01][0-9]-\d{4})");
inline std::regex universalRegex{ ".*" };
inline std::regex nameRegex("^[A-Za-z]+(?: [A-Za-z]+)*$");
inline std::regex genderRegex("^(male|female|other)$", std::regex_constants::icase);
inline std::regex salaryRegex("^(100000000(\\.0+)?|([1-9]\\d{0,7}|0)(\\.\\d+)?)$");
inline std::regex oneOrTwoDigitRegex("^\\d{1,2}$");
inline std::regex nonEmptyRegex("^.+$");
inline std::regex idRegex("^(?:[1-9]\\d{0,5}|999999)$");
inline std::regex realNumberRegex("^-?\\d*\\.?\\d+$");
inline std::regex yesNoRegex("^[YNyn]$");
inline std::regex validTypes("^(int|integer|varchar|date|float)$", std::regex_constants::icase);



inline void clearDisplay() {
	system("CLS");
}

inline std::string getInGreen(const std::string& str) {
	return "\033[32m" + str + "\033[0m";
}
inline std::string getInRed(const std::string& str) {
	return "\033[31m" + str + "\033[0m";
}
inline std::string getInBlue(const std::string& str) {
	return "\033[34m" + str + "\033[0m";
}
inline std::string getInYellow(const std::string& str) {
	return "\033[33m" + str + "\033[0m";
}
inline std::string getInMagenta(const std::string& str) {
	return "\033[35m" + str + "\033[0m";
}
inline std::string getInCyan(const std::string& str) {
	return "\033[36m" + str + "\033[0m";
}


inline void waitBeforeClear() {
	std::cout << getInYellow("\n- Press Enter to continue...");
	std::string line;
	std::getline(std::cin, line);
}

template<typename T>
void displayVector(const std::vector<T>& coll) {
	clearDisplay();
	std::cout << "<----------------------------- " << getInCyan(std::to_string(coll.size()) + " - Records Found ")  << " ------------------------------>\n";
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

	std::cout << getInYellow("\n<---------------------------------------------------------------------------------------------------------------------->\n");

	std::cout<< "                                  " << getInCyan("  __        __   _                            _ \n");
	std::cout<< "                                  " << getInCyan("  \\ \\      / /__| | ___ ___  _ __ ___   ___  | |\n") ;
	std::cout<< "                                  " << getInCyan("   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | |\n");
	std::cout<< "                                  " << getInCyan("    \\ V  V /  __/ | (_| (_) | | | | | |  __/ |_|\n");
	std::cout<< "                                  " << getInCyan("     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___| (_)\n");

	std::cout << getInCyan("\n<--------------------------------------------> ") << getInYellow("EMPLOYEE MANAGEMENT SYSTEM") << getInCyan(" <-------------------------------------------->\n");
	
	std::cout << "\n\n1. Employee Menu     \n";
	std::cout <<   "2. Department Menu   \n";
	std::cout <<   "3. Engineer Menu     \n";
	std::cout <<   "4. Manager Menu      \n";
	std::cout <<   "5. Salary Menu       \n";
	std::cout <<   "6. General Table Menu\n";
	std::cout <<   "7. Export To CSV\n";
	std::cout <<   "8. Quit              \n\n";

	
}

inline void displayThanks() {
	clearDisplay();
	std::cout << "                                  " << getInYellow("  _______ _                 _     __     __         \n");
	std::cout << "                                  " << getInYellow(" |__   __| |               | |    \\ \\   / /         \n");
	std::cout << "                                  " << getInYellow("    | |  | |__   __ _ _ __ | | __  \\ \\_/ ___  _   _ \n");
	std::cout << "                                  " << getInYellow("    | |  | '_ \\ / _` | '_ \\| |/ /   \\   / _ \\| | | |\n");
	std::cout << "                                  " << getInYellow("    | |  | | | | (_| | | | |   <     | | (_) | |_| |\n");
	std::cout << "                                  " << getInYellow("    |_|  |_| |_|\\__,_|_| |_|_|\\_\\    |_|\\___/ \\__,_|\n");
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
		std::cout << getInRed("Invalid Input!\n");
	}
}

inline std::string inputWithQuit(std::string_view prompt, std::optional<std::regex> r = universalRegex, bool allowSkip = false) {
	std::string ip;

	while (1) {
		std::cout << prompt;

		std::getline(std::cin, ip);

		if (ip == ":q") {
			throw -1;
		}
		if (allowSkip && ip == "#") {
			return "#";
		}

		if (std::regex_match(ip, r.value_or(universalRegex))) {
			return ip;
		}

		std::cout << getInRed("Invalid Input! - ") << "Please enter valid input or " << getInRed("':q'") << " to quit.\n";
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












