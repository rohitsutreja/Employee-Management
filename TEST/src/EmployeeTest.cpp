#include "../Fixtures/EmployeeFixture.h"

TEST_F(EmployeeFixture, employeeSave) {
	//Employee Without manager (id 103)
	EXPECT_TRUE(emp1.save());

	//Employee with manager id which does not exist.(id 104)
	EXPECT_FALSE(emp2.save());

	//Employee without  department id (id 105)
	EXPECT_FALSE(emp3.save());

	//New Employee with id that already exists(duplicate entry)
	EXPECT_FALSE(emp1.save());

	//Employee with department that does not exists
	EXPECT_FALSE(emp8.save());

}

TEST_F(EmployeeFixture, employeeRead) {
	ASSERT_EQ(Employee::getEmployeeById(1000), std::nullopt);
	ASSERT_EQ(Employee::getEmployeeById(103)->getFirstname(), "Rohit");
	ASSERT_EQ(Employee::getEmployeeById(103)->getId(), 103);
	ASSERT_NE(Employee::getEmployeeById(103)->getId(), 104);
}

TEST_F(EmployeeFixture, employeeReadMultiple) {
	ASSERT_EQ(Employee::getMultipleEmployee("firstname", "rajuraju").size(), 0);
	ASSERT_EQ(Employee::getMultipleEmployee("firstname", "Rohit").size(), 4);
	ASSERT_EQ(Employee::getMultipleEmployee("Department.name", "C++").size(), 4);
}

TEST_F(EmployeeFixture, employeeUpdate) {
	//Updating employee that does not exist (id 0)
	EXPECT_FALSE(emp0.update());

	//Employee update but without manager; (id 103)
	EXPECT_TRUE(emp1.update());

	//Employee update with manager id which exist in employee but does not exist in manager table. (id )
	EXPECT_FALSE(emp4.update());

	//Employee update with manager id that exist in manager table
	EXPECT_TRUE(emp5.update());

	//Employee update with department id that does not exist. 
	EXPECT_FALSE(emp6.update());
}

TEST_F(EmployeeFixture, employeeDelete) {
	//Delete employee which is manager of some employees (id 301)
	EXPECT_FALSE(emp7.deleteThis());

	//Delete employee which is manager of some department (id 301)
	EXPECT_FALSE(emp7.deleteThis());

	//DELETE emmployee which is not manager of any employee or department (id 103)
	EXPECT_TRUE(emp1.deleteThis());

}
