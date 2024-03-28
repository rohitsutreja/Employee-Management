#pragma once
#pragma once
#include "gtest/gtest.h"
#include "include/Entities/Department.h"
using Entity::Department;


class DepartmentFixture : public testing::Test {
protected:
	void SetUp() {

		//INSERT ---------------------------------------------------

		//Department without manager
		d1.setId(402);
		d1.setName("A Department");
		d1.setManagerId(-1);
		d1.setDescription("OK");

		//Department with manager id that does not exists in any table
		d2 = d1;
		d2.setId(403);
		d2.setManagerId(5000);

		//Department with manager id that does not exist in manager table but exists in employee table
		d3 = d1;
		d3.setId(404);
		d3.setManagerId(107);

		//Department that alredy exists
		d4 = d1;

		//Department with valid manager
		d5 = d1;
		d5.setId(405);
		d5.setManagerId(302);

		
		//UPDATE --------------------------------------------------

		//Department that does not exists
		d0.setId(5000);

		//Removing Manager
		d6 = d5;
		d6.setManagerId(-1);

		//Updating Manager ID that not exist in manager but exists in employee
		d7 = d1;
		d7.setManagerId(107);

		//Updating with valid manager ID
		d8 = d1;
		d8.setManagerId(301);


		//DELETE ---------------------------------------------------

		//department with employyes in the department
		d9 = d1;
		d9.setId(401);

		//Delete empty department without manager
		d1;

		//Delete empty department with manaager
		d5;

		//Delete department that does not exists
		d0;

	}

	Department d0;
	Department d1;
	Department d2;
	Department d3;
	Department d4;
	Department d5;
	Department d6;
	Department d7;
	Department d8;
	Department d9;
};