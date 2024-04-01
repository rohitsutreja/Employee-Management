#include "include/View/Menu.h"
#include "include/Entities/Table.h"


int main()
{
	try {
		auto dbI = DB::getDB();
		dbI->open("Rohit.db");

		runMenu();
	}
	catch (...) {
		clearDisplay();
		std::cout << getInRed("Severe Unexpected Error!!!");
	}

	return 0;
}
