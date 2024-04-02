#include "../Fixtures/EngineerFixture.h"


TEST_F(EngineerFixture, engineersave) {
	//Engineer Without manager 
	EXPECT_TRUE(eng1.save());

	//Engineer with manager id which does not exist.
	EXPECT_FALSE(eng2.save());

	//Engineer without department id 
	EXPECT_FALSE(eng3.save());

	//New Engineer with id that already exists(duplicate entry)
	EXPECT_FALSE(eng4.save());

	//Engineer with department that does not exists
	EXPECT_FALSE(eng8.save());

}

TEST_F(EngineerFixture, engineerRead) {
	ASSERT_EQ(Engineer::getEngineerById(1000), std::nullopt);
	ASSERT_EQ(Engineer::getEngineerById(112)->getFirstname(), "rajesh");
	ASSERT_EQ(Engineer::getEngineerById(113)->getId(), 113);
	ASSERT_EQ(Engineer::getEngineerById(112)->getDepartmentId(), 450);
	ASSERT_NE(Engineer::getEngineerById(113)->getId(), 110);
}

TEST_F(EngineerFixture, engineerReadMultiple) {
	ASSERT_EQ(Engineer::getMultipleEngineers("firstname", "naineel").back().getFirstname(), "naineel");
	ASSERT_EQ(Engineer::getMultipleEngineers("programming_language", "javascript").size(), 1);
	ASSERT_EQ(Engineer::getMultipleEngineers("Department.name", "OS").size(), 2);
}

TEST_F(EngineerFixture, engineerUpdate) {
	//Updating Engineer that does not exist (id 0)
	EXPECT_FALSE(eng0.update());

	//Engineer update but without manager; (id 103)
	EXPECT_TRUE(eng1.update());

	//Engineer update with manager id which exist in employee but does not exist in manager table. (id )
	EXPECT_FALSE(eng4.update());

	//Engineer update with manager id that exist in manager table
	EXPECT_TRUE(eng5.update());

	//Engineer update with department id that does not exist. 
	EXPECT_FALSE(eng6.update());
}

TEST_F(EngineerFixture, engineerDelete) {
	//DELETE Engineer that does not exists
	EXPECT_FALSE(eng7.deleteThis());

	//Delete valid engineer
	EXPECT_TRUE(eng9.deleteThis());

}
