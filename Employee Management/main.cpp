#include <iostream>
#include "sqlite/sqlite3.h"
#include"include/Employee.h"
int main()
{

    sqlite3* db;
    char* errMsg = 0;

    int rc = sqlite3_open("employee.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << '\n';
        sqlite3_close(db);
        return 1;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Employee ("
                      "employeeId INTEGER PRIMARY KEY, "
                      "name TEXT NOT NULL, "
                      "age INTEGER NOT NULL, "
                      "designation TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << '\n';
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    std::cout << "Table created successfully.\n";

    sqlite3_close(db);
    Employee emp(1, "Rohit", 22, "Software Engineer");
    emp.createRecord();
    emp.updateRecord();

   // emp.deleteRecord();


    return 0;
}
