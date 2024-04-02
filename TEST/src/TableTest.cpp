#include "gtest/gtest.h"
#include "../Fixtures/TableFixture.h"

TEST_F(TableFixture, TableSave) {
	//Table "Human" with two fields
	EXPECT_TRUE(t1.save());

	//Table "---" - invalid name
	EXPECT_FALSE(t2.save());

	//TAble "Entity" with no fields from user, id auto inserted
	EXPECT_TRUE(t3.save());
}

TEST_F(TableFixture, TableRead) {
	ASSERT_EQ(Table::getTable("Human")->getName(), "Human");
	ASSERT_EQ(Table::getTable("Entity")->getName(), "Entity");
	ASSERT_EQ(Table::getTable("Human")->getNoOfFields(), 3);
	ASSERT_EQ(Table::getTable("NoTAble"), std::nullopt);
}

TEST_F(TableFixture, TableReadMultiple) {
	ASSERT_EQ(Table::getAllTables().size(),7 );

}

TEST_F(TableFixture, TableDelete) {
	EXPECT_TRUE(t1.deleteThis());
	EXPECT_TRUE(t3.deleteThis());

	//Invalid name "---"
	EXPECT_FALSE(t2.deleteThis());
}

TEST_F(TableFixture, TableAddFields){
	EXPECT_TRUE(t4.addKeyTypePair("age", "int"));
	EXPECT_TRUE(t4.addKeyTypePair("name","varchar"));
	
	//id is automaticly added

	ASSERT_EQ(t4.getNoOfFields(),3);
}
