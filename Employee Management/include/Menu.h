#pragma once

#include <iostream>
#include "../sqlite/sqlite3.h"
#include "Entities/Employee.h"
#include "DB.h"
#include "Regex.h"
#include "Entities/Department.h"
#include "Entities/Engineer.h"
#include "Entities/Manager.h"


void runEmployeeMenu();

void runEngineerMenu();

void runManagerMenu();

void runDepartmentMenu();

void runSalaryMenu();

void runMenu();

