#include <iostream>
#include "sqlite/sqlite3.h"
#include"include/Employee.h"
#include "include/DB.h"
#include "include/Regex.h"
#include "include/Department.h"


void runEmployeeMenu(){
    int choice{};

    while (1) {
        std::cout << "Please select an option: \n";

        std::cout << "1. Insert an Employee\n";
        std::cout << "2. Update an Employee\n";
        std::cout << "3. View an Employee\n";
        std::cout << "4. Delete an Employee\n";
        std::cout << "5. Main menu\n";

    }
}

void runDepartmentMenu(){
    int choice{};
    while (1) {
        std::cout << "Please select an option: \n";

        std::cout << "1. Insert an Department\n";
        std::cout << "2. Update an Department\n";
        std::cout << "3. View an Department\n";
        std::cout << "4. Delete an Department\n";
        std::cout << "5. Main menu\n";


        std::cin >> choice;
    }
}


int main()
{   


    std::cout << "--------------------------------------------WELCOME--------------------------------------------";


    int choice{};
    while (1) {
        std::cout << "1. Employee Menu\n";
        std::cout << "2. Department Menu\n";
        std::cout << "3. Quit\n";

        std::cin >> choice;

        if (choice == 1) {
            runEmployeeMenu();
        }
        else if (choice == 2) {
            runDepartmentMenu();

        }
        else if (choice == 3) {
            std::cout << "Thank You\n";
            break;
        }
    }


    return 0;
}
