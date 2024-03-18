#ifndef DBH
#define DBH

#include <iostream>
#include "../sqlite/sqlite3.h"
#include "Logger/MyLogger.h"

class DB
{
    sqlite3* db{};
    char* errMsg{};
    int rc{};

public:
    DB(const char* str);

    bool createTables();

    bool executeQuery(const char* sql, const std::string&msg = "");

    bool executeSelectQuery(const char* selectQuery, int(*selectCallback)(void*, int, char**, char**), void* data, const std::string& msg = "");

    static std::shared_ptr<DB> getDB();

    ~DB();
};

#endif