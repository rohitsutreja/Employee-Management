#pragma once

#include<regex>

inline std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
inline std::regex mobileRegex(R"([0-9]{10})");
inline std::regex dateRegex(R"([0-3][0-9]-[01][0-9]-\d{4})");
inline std::regex choiceRegex("^[0-9]$");
inline std::regex mainChoiceRegex("^[1-6]$");
inline std::regex universalRegex{ ".*" };
inline std::regex nameRegex("^[A-Za-z]+(?: [A-Za-z]+)*$");
inline std::regex genderRegex("^(male|female|other)$", std::regex_constants::icase);
inline std::regex salaryRegex("^[+]?\\d*\\.?\\d+$");
inline std::regex oneOrTwoDigitRegex("^\\d{1,2}$");
inline std::regex nonEmptyRegex("^.+$");
inline std::regex idRegex("^(?:[1-9]\\d{0,3}|9999)$");
