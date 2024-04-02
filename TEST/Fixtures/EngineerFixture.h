#pragma once
#include "gtest/gtest.h"
#include "include/Entities/Employee.h"
#include "include/Entities/Engineer.h"

using::Entity::Engineer;
using::Entity::Salary;
using::Entity::Employee;

class EngineerFixture : public testing::Test {
protected:
	void SetUp() {
		//Engineer Without Manager and valid department
		eng1.setId(203);
		eng1.setFirstname("Rohit");
		eng1.setLastname("Sutreja");
		eng1.setDob("19-12-2002");
		eng1.setGender(Employee::Gender::Male);
		eng1.setAddress("Junagadh");
		eng1.setMobile("9106479126");
		eng1.setEmail("rohit@gmail.com");
		eng1.setDoj("19-12-2021");
		eng1.setManagerId(-1);
		eng1.setDepartmentId(401);
		eng1.setProgrammingLanguage("CPP");
		eng1.setSpecialization("BIM DEV");
		sal1.setID(203);
		sal1.setBaseSalary(500000);
		sal1.setBonus(100000);
		eng1.setSalary(sal1);

		//Engineer with manager that does not exist and valid department
		eng2 = eng1;
		eng2.setId(204);
		eng2.setManagerId(305);

		sal2 = sal1;
		sal2.setID(204);

		eng2.setSalary(sal2);

		//Engineer with no department 
		eng3 = eng1;
		eng3.setId(205);

		eng3.setDepartmentId(-1);

		sal3 = sal2;
		sal3.setID(205);

		eng3.setSalary(sal3);

	
		//Engineer with department that does not exist.
		eng8 = eng1;
		eng8.setId(206);
		eng8.setDepartmentId(405);

		sal8 = sal1;
		sal8.setID(206);
		eng8.setSalary(sal8);


		//UPDATE --------------------------------------------------

		//Employee update with manager id which exist in employee but does not exist in manager table. (id )
		eng4 = eng1;
		eng4.setManagerId(102);


		//Employee update with manager id that exist in manager table
		eng5 = eng1;
		eng5.setManagerId(301);

		//Employee update with department id that does not exist. 
		eng6 = eng1;
		eng6.setManagerId(301);
		eng6.setDepartmentId(400);


		//DELETE ---------------------------------------------------
		eng7 = eng1;
		eng7.setId(210);

		eng9 = eng1;
		eng1.setId(203);


	}


	Engineer eng0;
	Salary sal0;

	Engineer eng1;
	Salary sal1;

	Engineer eng2;
	Salary sal2;

	Engineer eng3;
	Salary sal3;

	Engineer eng4;
	Salary sal4;

	Engineer eng5;
	Salary sal5;

	Engineer eng6;
	Salary sal6;

	Engineer eng7;
	Salary sal7;

	Engineer eng8;
	Salary sal8;

	Engineer eng9;
	Salary sal9;

	Engineer eng10;
	Salary sal10;
};