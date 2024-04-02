#pragma once
#include "gtest/gtest.h"
#include "include/Entities/Table.h"

class TableFixture : public testing::Test {
protected:
	void SetUp() {
		t1.setName("Human");
		t1.addKeyTypePair("name", "varchar");
		t1.addKeyTypePair("age", "int");

		t2.setName("---");
		t2.addKeyTypePair("name", "varchar");
		t2.addKeyTypePair("age", "int");

		t3.setName("Entity");
	


	}

	Table t1;
	Table t2;
	Table t3;
	Table t4;
};