#pragma once
#include "gtest/gtest.h"
#include "include/Entities/Employee.h"

class EmployeeFixture : public testing::Test {
protected:
	void SetUp() {
		//Employee Without Manager and valid department
		emp1.setId(103);
		emp1.setFirstname("Rohit");
		emp1.setLastname("Sutreja");
		emp1.setDob("19-12-2002");
		emp1.setGender(Employee::Gender::Male);
		emp1.setAddress("Junagadh");
		emp1.setMobile("9106479126");
		emp1.setEmail("rohit@gmail.com");
		emp1.setDoj("19-12-2021");
		emp1.setManagerId(-1);
		emp1.setDepartmentId(401);
		sal1.setID(103);
		sal1.setBaseSalary(500000);
		sal1.setBonus(100000);
		emp1.setSalary(sal1);

		//Employee with manager that does not exist and valid department
		emp2 = emp1;
		emp2.setId(104);
		emp2.setManagerId(305);

		sal2 = sal1;
		sal2.setID(104);

		emp2.setSalary(sal2);

		//Employee with no department 
		emp3 = emp1;
		emp3.setId(105);
		emp3.setDepartmentId(-1);

		sal3 = sal2;
		sal3.setID(105);

		emp3.setSalary(sal3);


		//Employee with department that does not exist.
		emp8 = emp1;
		emp8.setId(106);
		emp8.setDepartmentId(405);

		sal8 = sal1;
		sal8.setID(106);
		emp8.setSalary(sal8);
		//UPDATE --------------------------------------------------

		//Employee update with manager id which exist in employee but does not exist in manager table. (id )
		emp4 = emp1;
		emp4.setManagerId(102);


		//Employee update with manager id that exist in manager table
		emp5 = emp1;
		emp5.setManagerId(301);

		//Employee update with department id that does not exist. 
		emp6 = emp1;
		emp5.setManagerId(301);
		emp6.setDepartmentId(400);


		//DELETE ---------------------------------------------------
		emp7 = emp1;
		emp7.setId(301);



	}


	Employee emp0;
	Salary sal0;

	Employee emp1;
	Salary sal1;

	Employee emp2;
	Salary sal2;

	Employee emp3;
	Salary sal3;

	Employee emp4;
	Salary sal4;

	Employee emp5;
	Salary sal5;

	Employee emp6;
	Salary sal6;

	Employee emp7;
	Salary sal7;

	Employee emp8;
	Salary sal8;

	Employee emp9;
	Salary sal9;

	Employee emp10;
	Salary sal10;


};