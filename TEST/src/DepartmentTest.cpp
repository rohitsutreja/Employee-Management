#include "../Fixtures/DepartmentFixture.h"

TEST_F(DepartmentFixture, departmentSave) {
	//Department without manager
	EXPECT_TRUE(d1.save());

	//Department with manager id that does not exists in any table
	EXPECT_FALSE(d2.save());

	//Department with manager id that does not exist in manager table but exists in employee table
	EXPECT_FALSE(d3.save());

	//Department that alredy exists
	EXPECT_FALSE(d4.save());

	//Department with valid manager
	EXPECT_TRUE(d5.save());
}

TEST_F(DepartmentFixture, departmentRead) {
	ASSERT_EQ(Department::getDepartmentById(1000), std::nullopt);
	ASSERT_EQ(Department::getDepartmentById(401)->getName(), "C++");
	ASSERT_EQ(Department::getDepartmentById(402)->getId(), 402);
	ASSERT_NE(Department::getDepartmentById(402)->getId(), 500);
}

TEST_F(DepartmentFixture, departmentReadMultiple) {
	ASSERT_EQ(Department::getMultipleDepartment("name", "A Department").size(), 2);
	ASSERT_EQ(Department::getMultipleDepartment("Department.manager_id", "302").size(), 1);
	ASSERT_EQ(Department::getMultipleDepartment("Department.name", "C++").size(), 1);
	ASSERT_EQ(Department::getMultipleDepartment("Department.name", "C++").back().getId(), 401);
}

TEST_F(DepartmentFixture, departmentUpdate) {
	//Department that does not exists
	EXPECT_FALSE(d0.update());

	//Removing Manager
	EXPECT_TRUE(d6.update());

	//Updating Manager ID that not exist in manager but exists in employee
	EXPECT_FALSE(d7.update());

	//Updating with valid manager ID
	EXPECT_TRUE(d8.update());
}

TEST_F(DepartmentFixture, departmentDelete) {
	//department with employyes in the department
	EXPECT_FALSE(d9.deleteThis());

	//Delete empty department without manager
	EXPECT_TRUE(d1.deleteThis());

	//Delete empty department with manaager.
	EXPECT_TRUE(d5.deleteThis());

	//Delete department that does not exists
	EXPECT_FALSE(d0.deleteThis());
}
