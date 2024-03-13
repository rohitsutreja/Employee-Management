#include "../include/DB.h"
#include"../include/Logger/MyLogger.h"

//bool DB::open(const char* str) {
//        rc = sqlite3_open(str, &db);
//        if (rc)
//        {
//            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//            return false;
//        }
//        else
//        {
//            MyLogger::info("Opened database successfully");
//            //std::cout << "Opened database successfully" << std::endl;
//            return true;
//        }
//
//    }

bool DB::createTables() {

        const char* sql = "CREATE TABLE IF NOT EXISTS Employee ("
            "id INTEGER PRIMARY KEY,"
            "firstname VARCHAR,"
            "lastname VARCHAR,"
            "dob DATE,"
            "mobile VARCHAR,"
            "email VARCHAR,"
            "address VARCHAR,"
            "gender VARCHAR CHECK (gender IN ('Male', 'Female', 'Other')),"
            "doj DATE,"
            "manager_id INTEGER,"
            "department_id INTEGER,"
            "FOREIGN KEY (department_id) REFERENCES Department(id),"
            "FOREIGN KEY (manager_id) REFERENCES Employee(id));";

        if (!executeQuery(sql))
        {
            return false;
        }

        const char* sql2 = "CREATE TABLE IF NOT EXISTS Department ("
            "id INTEGER PRIMARY KEY,"
            "name VARCHAR,"
            "manager_id INTEGER,"
            "description VARCHAR,"
            "FOREIGN KEY (manager_id) REFERENCES Employee(id))";


        if (!executeQuery(sql2))
        {
            return false;
        }




        const char* sql3 = "CREATE TABLE IF NOT EXISTS Engineer ("
            "id INTEGER PRIMARY KEY,"
            "programming_language VARCHAR,"
            "specialization VARCHAR,"
            "FOREIGN KEY (id) REFERENCES Employee(id))";

        if (!executeQuery(sql3))
        {
            return false;
        }



        const char* sql4 = "CREATE TABLE IF NOT EXISTS Manager ("
            "id INTEGER PRIMARY KEY,"
            "management_experience INTEGER,"
            "project_title VARCHAR,"
            "FOREIGN KEY (id) REFERENCES Employee(id))";


        if (!executeQuery(sql4))
        {
            return false;
        }



        const char* sql5 = "CREATE TABLE IF NOT EXISTS Salary ("
            "id INTEGER PRIMARY KEY,"
            "amount INTEGER,"
            "base_salary INTEGER,"
            "bonus INTEGER,"
            "FOREIGN KEY (id) REFERENCES Employee(id))";

        if (!executeQuery(sql5))
        {
            return false;
        }


        return true;
    }

bool DB::executeQuery(const char* sql, std::string_view msg)
    {
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }
        else
        {
            std::cout << msg << std::endl;
            return true;
        }
    }

    bool DB::executeSelectQuery(const char* selectQuery, int(*selectCallback)(void*, int, char**, char**), void* data, std::string_view msg) {


        rc = sqlite3_exec(db, selectQuery, selectCallback, data, nullptr);

        if (rc != SQLITE_OK) {
            std::cerr << "Error executing query: " << sqlite3_errmsg(db) << std::endl;
           
            return false;
        }
        else {
            std::cout << msg;
            return true;
        }
    }

DB::~DB()
{
   sqlite3_close(db);
}
