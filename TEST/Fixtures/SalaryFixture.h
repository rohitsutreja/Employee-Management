#pragma once
#pragma once
#pragma once
#include "gtest/gtest.h"
#include "include/Entities/Department.h"

class SalaryFixture : public testing::Test {
protected:
	void SetUp() {

		//INSERT ---------------------------------------------------

		//Salary without employee
		s1.setID(50);
		s1.setBaseSalary(1000000);
		s1.setBonus(100000);

		//salary with existing valid employee id
		s2 = s1;
		s2.setID(110);

		//duplicate salary
		s3 = s1;
		s3.setID(110);

		//UPDATE --------------------------------------------------

		//Updating salary that does not exists.
		s0.setID(500);

		//DELETE ---------------------------------------------------

		//deletig salary that does not exists.
		s0.setID(500);

		//deleting salary of existing employee
		s4 = s1;
		s4.setID(110);

	}

	Salary s0;
	Salary s1;
	Salary s2;
	Salary s3;
	Salary s4;
};