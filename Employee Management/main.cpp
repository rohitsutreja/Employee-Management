#include "include/Menu.h"
#include "include/Entities/Table.h"
int main()
{
	auto dbI = DB::getDB();
	dbI->open("C:\\Users\\ZTI\\source\\repos\\Employee Management\\Employee Management\\Rohit.db");
	//runMenu();

	//Table t;
	//t.getUserInputForTable();
	//t.save();

	auto t1 = Table::getTable("Salary");

	if (t1) t1->display();
	else std::cout << "Does not exists";

	return 0;
}
