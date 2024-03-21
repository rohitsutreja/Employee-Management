#pragma once
#include "gtest/gtest.h"
#include "include/Entities/Employee.h"
#include "include/Entities/Manager.h"
#include "include/Entities/Manager.h"

class ManagerFixture : public testing::Test {
protected:
	void SetUp() {
		//Manager Without Manager and valid department
		mng1.setId(303);
		mng1.setFirstname("Rohit");
		mng1.setLastname("Sutreja");
		mng1.setDob("19-12-2002");
		mng1.setGender(Employee::Gender::Male);
		mng1.setAddress("Junagadh");
		mng1.setMobile("9106479126");
		mng1.setEmail("rohit@gmail.com");
		mng1.setDoj("19-12-2021");
		mng1.setManagerId(-1);
		mng1.setDepartmentId(401);
		mng1.setManagementExperience(10);
		mng1.setProjectTitle("DC");
		sal1.setID(303);
		sal1.setBaseSalary(500000);
		sal1.setBonus(100000);
		mng1.setSalary(sal1);

		//Manager with manager that does not exist and valid department
		mng2 = mng1;
		mng2.setId(304);
		mng2.setManagerId(305);

		sal2 = sal1;
		sal2.setID(304);

		mng2.setSalary(sal2);

		//Manager with no department 
		mng3 = mng1;
		mng3.setId(305);
		mng3.setDepartmentId(-1);

		sal3 = sal2;
		sal3.setID(305);

		mng3.setSalary(sal3);


		//Manager with department that does not exist.
		mng8 = mng1;
		mng8.setId(306);
		mng8.setDepartmentId(405);

		sal8 = sal1;
		sal8.setID(306);
		mng8.setSalary(sal8);


		//UPDATE --------------------------------------------------

		//Employee update with manager id which exist in employee but does not exist in manager table. (id )
		mng4 = mng1;
		mng4.setManagerId(102);


		//Employee update with manager id that exist in manager table
		mng5 = mng1;
		mng5.setManagerId(302);

		//Employee update with department id that does not exist. 
		mng6 = mng1;
		mng6.setManagerId(301);
		mng6.setDepartmentId(50000);


		//DELETE ---------------------------------------------------
		mng7 = mng1;
		mng7.setId(301);

		mng9 = mng1;
		mng9.setId(303);

	


	}


	Manager mng0;
	Salary sal0;

	Manager mng1;
	Salary sal1;

	Manager mng2;
	Salary sal2;

	Manager mng3;
	Salary sal3;

	Manager mng4;
	Salary sal4;

	Manager mng5;
	Salary sal5;

	Manager mng6;
	Salary sal6;

	Manager mng7;
	Salary sal7;

	Manager mng8;
	Salary sal8;

	Manager mng9;
	Salary sal9;

	Manager mng10;
	Salary sal10;
};