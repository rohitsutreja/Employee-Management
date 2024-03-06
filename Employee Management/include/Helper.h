#pragma once

#include<string>
#include <iostream>
#include <regex>

std::regex rg{ ".*" };

inline std::string input(const std::string& prompt, std::regex r = rg) {
	std::string ip;

	while (1) {

		std::cout << prompt;

		std::getline(std::cin, ip);
		


		if (ip == "#") { return "#"; }

		if(std::regex_match(ip, r)) {
			return ip;
		}
		
		std::cout << "Please Enter Valid Input\n";

	}
}