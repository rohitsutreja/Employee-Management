#pragma once

#include<string>
#include <iostream>
#include <regex>

std::regex rg{ ".*" };

inline std::string input(const std::string& prompt, std::regex r = rg) {
	std::string temp;

	while (1) {

		std::cout << prompt;
		std::cin >> temp;

		if(std::regex_match(temp, r)) {
			return temp;
		}
		
		std::cout << "Please Enter Valid Input\n";

	}
}