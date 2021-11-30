#include "..\stack1\Calc.h"
#include "gtest.h"

TEST(Calc, can_create_calc) 
{
	ASSERT_NO_THROW(Calc calc);
}
TEST(Calc, can_set_get)
{
	Calc calc;
	string exp = "3+9-8", res;
	ASSERT_NO_THROW(calc.SetExp(exp));
	calc.SetExp(exp);
	ASSERT_NO_THROW(res=calc.GetExp());
	res = calc.GetExp();
	EXPECT_EQ(res, exp);
}
TEST(Calc, expression_check) 
{
	Calc calc;
	string exp = "(3+9)*2";
	calc.SetExp(exp);
	ASSERT_NO_THROW(calc.CheckExp());
	EXPECT_TRUE(calc.CheckExp());
	calc.SetExp("(((5-9)");
	EXPECT_FALSE(calc.CheckExp());
}
TEST(Calc, postfix_convertation)
{
	Calc calc;
	calc.SetExp("1+2");
	ASSERT_NO_THROW(calc.PostEdit());
	EXPECT_EQ(calc.GetPost(), "1 2 +");
	calc.SetExp("(3-9)*5^(2-6)");
	calc.PostEdit();
	EXPECT_EQ(calc.GetPost(), "3 9 - 5 2 6 - ^ *");
}
TEST(Calc, operands_check)
{
	Calc calc;
	calc.SetExp("2+3");
	calc.PostEdit();
	EXPECT_EQ(calc.CalcPost(), 2 + 3);
	EXPECT_EQ(calc.Calculate(), 2 + 3);

	calc.SetExp("2-3");
	calc.PostEdit();
	EXPECT_EQ(calc.CalcPost(), 2 - 3);
	EXPECT_EQ(calc.Calculate(), 2 - 3);

	calc.SetExp("2*3");
	calc.PostEdit();
	EXPECT_EQ(calc.CalcPost(), 2*3);
	EXPECT_EQ(calc.Calculate(), 2*3);

	calc.SetExp("2/3");
	calc.PostEdit();
	EXPECT_EQ(calc.CalcPost(), double(2)/3);
	EXPECT_EQ(calc.Calculate(), double(2)/3);

	calc.SetExp("2^3");
	calc.PostEdit();
	EXPECT_EQ(calc.CalcPost(), pow(2,3));
	EXPECT_EQ(calc.Calculate(), pow(2,3));
}
TEST(Calc, can_calculate) {
	Calc calc;
	calc.SetExp("(6+5)*9-(78+5)^(3-9*6)");
	calc.PostEdit();
	EXPECT_EQ(calc.CalcPost(), (6+5)*9-pow((78+5),(3-9*6)));
	EXPECT_EQ(calc.Calculate(), (6 + 5) * 9 - pow((78 + 5), (3 - 9*6)));
	calc.SetExp("(8 ^(1+1)^2+5) * 6 - ((3 + 7) * 2/6)");
	calc.PostEdit();
	EXPECT_EQ(calc.CalcPost(), (pow(8, pow((1 + 1),2)) + 5) * 6 - ((3 + 7) * double(2) / 6));
	EXPECT_EQ(calc.Calculate(), (pow(8, pow((1 + 1), 2)) + 5) * 6 - ((3 + 7) * double(2) / 6));
}