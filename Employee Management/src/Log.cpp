 #include <iostream>
#include <string_view>
#include "..\include\Logger\Log.h"
#include <fstream>

using MyLogger::Log;

auto  defaultLogger = std::make_shared<Log>();

std::string Log::getLevelName(Level l) const {

    switch (l) {
    case Level::Error:
        return "Error";

    case Level::Warning:
        return "Warning";

    case Level::Info:
        return "Info";

    case Level::Debug:
        return "Debug";

    case Level::Critical:
        return "Critical";

    default:
        return "";
    }


}

std::string Log::getColoredLevelName(Level l) const {

    switch (l) {
    case Log::Log::Level::Error:
        return "\033[31mError\033[0m";

    case Level::Warning:
        return "\033[33mWarning\033[0m";

    case Level::Info:
        return "\033[32mInfo\033[0m";

    case Level::Debug:
        return "Debug";

    case Level::Critical:
        return "\033[41;37mCritical\033[0m";

    default:
        return "";
    }


}

void Log::logOnConsole(const std::string& msg) const {
    std::cout << msg;
}

void Log::logOnFile(const std::string& msg, const std::string& fileName) const {
    std::ofstream ofs{ fileName ,std::ios::app};
    ofs << msg;

}

void Log::flushOnFile() const {
    if (m_buffer != "") {
        logOnFile(m_buffer, m_fPath);
        m_buffer = "";
    }
}

Log::~Log() {
    if (m_buffer != "") {
        logOnFile(m_buffer, m_fPath);
        m_buffer = "";
    }
}