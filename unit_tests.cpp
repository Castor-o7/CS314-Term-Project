#include "googletest/googletest/include/gtest/gtest.h"
#include "ManagerTerminal.h"
#include "ReportGenerator.h"
#include "Service.h"


TEST(validateMemberNumber, notEnoughDigits) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_FALSE(term.validateMemberNumber("123"));
}

TEST(validateMemberNumber, enoughDigits) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_TRUE(term.validateMemberNumber("123456789"));
}

TEST(validateProviderNumber, notEnoughDigits) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_FALSE(term.validateProviderNumber("123"));
}

TEST(validateProviderNumber, enoughDigits) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_TRUE(term.validateProviderNumber("123456789"));
}

TEST(validateState, numberInput) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_FALSE(term.validateState("1"));
}

TEST(validateState, tooLong) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_FALSE(term.validateState("OREGON"));
}

TEST(validateState, properInput) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_TRUE(term.validateState("OR"));
}

TEST(validateZipCode, tooShort) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_FALSE(term.validateZipCode("1"));
}

TEST(validateZipCode, tooLong) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_FALSE(term.validateZipCode("123456"));
}

TEST(validateZipCode, justRight) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_TRUE(term.validateZipCode("97211"));
}

TEST(validateZipCode, isAlpha) {
	ReportGenerator *r = nullptr;
	ManagerTerminal term(r);
	EXPECT_FALSE(term.validateZipCode("my neighborhood"));
}

TEST(getCode, isCode) {
	Service s("123456", "name", 12.34);
	ASSERT_EQ("123456", s.getCode());
}

TEST(getName, isName) {
	Service s("123456", "name", 12.34);
	ASSERT_EQ("name", s.getName());	
}

TEST(getFee, isFee) {
	Service s("123456", "name", 12.34);
	ASSERT_EQ(12.34, s.getFee());
}

TEST(getPName, isName) {
	Provider p("name", "123456789", "street", "portland", "OR", "97211");
	ASSERT_EQ("name", p.getName());
}

TEST(getPNumber, isNumber) {
	Provider p("name", "123456789", "street", "portland", "OR", "97211");
	ASSERT_EQ("123456789", p.getNumber());
}

TEST(getPStreetAddress, isAddress) {
	Provider p("name", "123456789", "street", "portland", "OR", "97211");
	ASSERT_EQ("street", p.getStreetAddress());
}

TEST(getPCity, isCity) {
	Provider p("name", "123456789", "street", "portland", "OR", "97211");
	ASSERT_EQ("portland", p.getCity());
}

TEST(getPState, isState) {
	Provider p("name", "123456789", "street", "portland", "OR", "97211");
	ASSERT_EQ("OR", p.getState());
}

TEST(getPZipCode, isZip) {
	Provider p("name", "123456789", "street", "portland", "OR", "97211");
	ASSERT_EQ("97211", p.getZipCode());
}

int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
