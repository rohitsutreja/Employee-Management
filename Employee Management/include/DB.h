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
    DB(const char* str) {
        rc = sqlite3_open(str, &db);
        if (rc)
        {
            MyLogger::error("Can't open database: ", sqlite3_errmsg(db));
        }
        else
        {
            MyLogger::info("Opened database successfully");
        }
    }

    //bool open(const char* str);

    bool createTables();

    bool executeQuery(const char* sql, const std::string&msg = "");

    bool executeSelectQuery(const char* selectQuery, int(*selectCallback)(void*, int, char**, char**), void* data, const std::string& msg = "");

    static std::shared_ptr<DB> getDB() {
        static DB dbI = DB("Rohit.db");
        static auto ptr = std::make_shared<DB>(dbI);
        return ptr;
    }



    ~DB();
};

#endif