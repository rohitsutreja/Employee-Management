#include "gtest/gtest.h"
#include "include/DB.h"

int main(int argc, char** argv) {
	auto dbI = DB::getDB();
	dbI->open("Rohit.db");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}