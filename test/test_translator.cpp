#include "translator.h"
#include <gtest.h>

TEST(Translator, can_create) {

	ASSERT_NO_THROW(Translator t("123"));
}

TEST(Translator, can_get_infix) {

	Translator t("(2+7)*9-60/2");
	ASSERT_NO_THROW(t.GetInfix());
}
TEST(Translator, can_get_postfix) {

	Translator t("(2+7)*9-60/2");
	ASSERT_NO_THROW(t.GetPostfix());
}

TEST(Translator, can_calculate) {

	Translator t("(2+7)*9-60/2");
	ASSERT_NO_THROW(t.Calculate());
}

TEST(Translator, test_calculating) {

	Translator t("(2+7)*9-60/2");
	ASSERT_NO_THROW(t.Calculate(), 51);
}

TEST(Translator, test_calculating_negative) {

	Translator t("30*2-70+4*(12/6)");
	ASSERT_NO_THROW(t.Calculate(), -2);
}

TEST(Translator, test_infix_form) {

	Translator t("6+2*1");
	ASSERT_EQ("6+2*1", t.GetInfix());
}

TEST(Translator, test_postfix_form) {

	Translator t("6+2*1");
	ASSERT_EQ("621*+", t.GetPostfix());
}

TEST(Translator, can_add) {

	Translator t("17+32");
	ASSERT_EQ(49.0, t.Calculate());
}

TEST(Translator, can_add_dot) {

	Translator t("17.5+32.5");
	ASSERT_EQ(50.0, t.Calculate());
}

TEST(Translator, can_subtract) {

	Translator t("32-17");
	ASSERT_EQ(15.0, t.Calculate());
}

TEST(Translator, can_subtract_dot) {

	Translator t("17.5-0.5");
	ASSERT_EQ(17.0, t.Calculate());
}

TEST(Translator, can_subtract_negative) {

	Translator t("17-32");
	ASSERT_EQ(-15.0, t.Calculate());

}

TEST(Translator, can_multiply) {

	Translator t("7*7");
	ASSERT_EQ(49.0, t.Calculate());
}

TEST(Translator, can_divide) {

	Translator t("11/2");
	ASSERT_EQ(5.5, t.Calculate());
}

TEST(Translator, can_throw_one) {

	Translator t("2*");
	EXPECT_ANY_THROW(t.Calculate());
}

TEST(Translator, not_can_div_zero) {

	Translator t("11/0");
	EXPECT_ANY_THROW(t.Calculate());
}