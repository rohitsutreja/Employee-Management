#include "include/View/Menu.h"
#include "include/Entities/Table.h"
int main()
{
	auto dbI = DB::getDB();
	dbI->open("C:\\Users\\ZTI\\source\\repos\\Employee Management\\Employee Management\\Rohit.db");
	runMenu();

	
	return 0;
}
