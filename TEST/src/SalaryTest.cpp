#include "../Fixtures/SalaryFixture.h"
#include "include/Entities/Salary.h"

TEST_F(SalaryFixture, salarySave) {

	//Salary without employee
	EXPECT_FALSE(s1.save());

	//salary with existing valid employee id
	EXPECT_TRUE(s2.save());

	//duplicate salary
	EXPECT_FALSE(s3.save());
}

TEST_F(SalaryFixture, salaryRead) {
	ASSERT_EQ(Salary::getSalaryByID(1000), std::nullopt);
	ASSERT_EQ(Salary::getSalaryByID(107)->getId(), 107);
	ASSERT_EQ(Salary::getSalaryByID(301)->computeSalary(), 150000);
	ASSERT_NE(Salary::getSalaryByID(301)->computeSalary(), 150001);
}

TEST_F(SalaryFixture, salaryReadMultiple) {
	ASSERT_EQ(Salary::getMultipleSalary("Department.name", "C++").size(), 3);
	ASSERT_EQ(Salary::getMultipleSalary("bonus", "100000").back().getBonus(), 100000);
	ASSERT_NE(Salary::getMultipleSalary("bonus", "100000").back().getBonus(), 100001);
	ASSERT_EQ(Salary::getMultipleSalary("firstname", "Rohit").size(), 3);
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

TEST_F(SalaryFixture, salaryCompute) {
	ASSERT_EQ(s1.computeSalary(), 1100000);
	ASSERT_NE(s1.computeSalary(), 1000000);
}

TEST_F(SalaryFixture, salaryIncrement) {
	//Increment base by 10%, which was 1000000.
	ASSERT_EQ(s1.increment(10), 1100000);
	ASSERT_NE(s1.increment(10), 1200000);
}
