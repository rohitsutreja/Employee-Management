#include "../Fixtures/ManagerFixture.h"


TEST_F(ManagerFixture, managerSave) {
	//Manager Without manager 
	EXPECT_TRUE(mng1.save());

	//manager with manager id which does not exist.
	EXPECT_FALSE(mng2.save());

	//manager without department id 
	EXPECT_FALSE(mng3.save());

	//New manager with id that already exists(duplicate entry)
	EXPECT_FALSE(mng4.save());

	//manager with department that does not exists
	EXPECT_FALSE(mng8.save());

}

TEST_F(ManagerFixture, managerRead) {
	ASSERT_EQ(Manager::getManagerById(1000), std::nullopt);
	ASSERT_EQ(Manager::getManagerById(301)->getFirstname(), "rohit");
	ASSERT_EQ(Manager::getManagerById(302)->getId(), 302);
	ASSERT_EQ(Manager::getManagerById(302)->getDepartmentId(), 450);
	ASSERT_EQ(Manager::getManagerById(302)->getManagementExperience(), 15);
	ASSERT_NE(Manager::getManagerById(303)->getId(), 110);
}

TEST_F(ManagerFixture, managerReadMultiple) {
	ASSERT_EQ(Manager::getMultipleManagers("firstname", "kesu").back().getId(), 310);
	ASSERT_EQ(Manager::getMultipleManagers("management_experience", "15").size(), 2);
	ASSERT_EQ(Manager::getMultipleManagers("project_title", "DC").size(), 3);
}

TEST_F(ManagerFixture, managerUpdate) {
	//Updating Manager that does not exist (id 0)
	EXPECT_FALSE(mng0.update());

	//Manager update but without manager; 
	EXPECT_TRUE(mng1.update());

	//Manager update with manager id which exist in employee but does not exist in manager table. (id )
	EXPECT_FALSE(mng4.update());

	//manager update with manager id that exist in manager table
	EXPECT_TRUE(mng5.update());

	//manager update with department id that does not exist. 
	EXPECT_FALSE(mng6.update());
}

TEST_F(ManagerFixture, managerDelete) {
	//DELETE Manager that does not exists
	EXPECT_FALSE(mng0.deleteThis());

	//Delete Manager that is manager of some employee or department
	EXPECT_FALSE(mng7.deleteThis());

	//Delete manager that is not manager of anyone currently
	EXPECT_TRUE(mng9.deleteThis());
}

