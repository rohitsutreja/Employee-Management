#pragma once

#include<regex>

inline std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
inline std::regex mobileRegex(R"([0-9]{10})");
inline std::regex dateRegex(R"([0-3][0-9]-[01][0-9]-\d{4})");
inline  std::regex idRegex(R"(\b\d{1,3}\b)");