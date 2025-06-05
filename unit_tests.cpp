#include "googletest/googletest/include/gtest/gtest.h"

int Factorial(int) {
	return 1;
}

TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(Factorial(0), 1);
}

int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
