#include <iostream>
#include "sqlite/sqlite3.h"
#include"include/Employee.h"
#include "include/DB.h"
int main()
{


    DB db1;
    db1.open("Emp.db");


    return 0;
}
