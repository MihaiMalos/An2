#include "pch.h"

class BoardTests : public testing::Test {

protected:
	void SetUp() override
	{

		a = new int(5);
	}

	void TearDown() override
	{
		if (a) delete a;
	}

protected:
	int* a;
};

TEST_F(BoardTests, PlaceColumn) {
	EXPECT_TRUE(*a == 5);

}