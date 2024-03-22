#include "pch.h"

#include"include/Util.h"
#include"include/Entities/Department.h"
#include"include/Entities/Manager.h"
#include"include/Entities/Employee.h"
#include"include/Entities/Engineer.h"

#include "Fixtures/EmployeeFixture.h"
#include "Fixtures/DepartmentFixture.h"
#include "Fixtures/SalaryFixture.h"
#include "Fixtures/EngineerFixture.h"
#include "Fixtures/ManagerFixture.h"

//EMPLOYEE
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


//DEPARTMENT
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



//SALARY
TEST_F(SalaryFixture, salarySave) {

	//Salary without employee
	EXPECT_FALSE(s1.save());

	//salary with existing valid employee id
	EXPECT_TRUE(s2.save());

	//duplicate salary
	EXPECT_FALSE(s3.save());
}

TEST_F(SalaryFixture, salaryUpdate) {
	//updating salary that does not exists.
	EXPECT_FALSE(s0.update());
}

TEST_F(SalaryFixture, salaryDelete) {
	//deleting salary of eployee that does not exsts.
	EXPECT_FALSE(s0.deleteThis());

	//deleting salary of existing employee
	EXPECT_TRUE(s4.deleteThis());
}


//ENGINEER
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


//MANAGER
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


int main(int argc, char** argv) {
	auto dbI = DB::getDB();
	dbI->open("Rohit.db");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}