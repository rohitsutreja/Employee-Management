#include"include/Util.h"
#include "gtest/gtest.h"

TEST(UTIL, getString) {
	ASSERT_EQ(getString("Hello ", "World"), "Hello World");
	ASSERT_NE(getString("Hello ", "World"), "HelloWorld");
	ASSERT_EQ(getString("This", " is", " Testing", " of", " Project"), "This is Testing of Project");
}