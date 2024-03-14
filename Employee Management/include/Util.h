#ifndef UTIL_H
#define UTIL_H


#include<string>
#include <iostream>
#include <regex>
#include <chrono>


namespace std {
	_EXPORT_STD _NODISCARD inline string to_string(const string& s) {
		return s;
	}

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




inline std::regex rg{ ".*" };

inline std::string input(const std::string& prompt, std::regex r = rg, bool allowSkip = false) {
	std::string ip;

	while (1) {

		std::cout << prompt;

		std::getline(std::cin, ip);
		if (allowSkip) {
			if (ip == "#") { return "#"; }
		}
		
		if(std::regex_match(ip, r)) {
			return ip;
		}
		
		std::cout << "\033[31mInValid Input!!\033[0m\n";

	}
}


std::string getLogTimeString();


void inline print() {};

template <typename T, typename... Types>
void print(const T& first, const Types&... args)
{
	std::cout << first << " ";
	print(args...);
}




std::string inline getString() { return ""; };

template <typename T, typename... Types>
std::string getString(const T& first, Types&... args)
{
	std::string result{ "" };
	result = result + std::to_string(first);
	result += getString(args...);

	return result;
}



#endif












