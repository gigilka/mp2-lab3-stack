#include "..\stack1\Stack.h"

#include "gtest.h"

TEST(Stack, can_create_stack_with_positive_size)
{
  ASSERT_NO_THROW(Stack<int> st(5));
}
TEST(Stack, cant_create_stack_with_non_positive_size)
{
	ASSERT_ANY_THROW(Stack<int> st(-9));
	ASSERT_ANY_THROW(Stack<int> st(0));
}
TEST(Stack, can_create_copied_stack_and_comparation)
{
	Stack<int> st(5);
	ASSERT_NO_THROW(Stack<int> stack = st);
	for (int i = 0; i < 5; i++) {
		st.Push(i);
	}
	Stack<int> stack = st;
	EXPECT_EQ(stack, st);
}
TEST(Stack, copied_stack_has_its_own_memory) 
{
	Stack<int> st(5);
	for (int i = 0; i < 5; i++) {
		st.Push(i);
	}
	Stack<int> stack= st;
	stack.Clear();
	for (int i = 0; i < 5; i++) {
		stack.Push(i + 1);
	}
	for (int i = 0; i < 5; i++) {
		EXPECT_NE(st.Pop(), stack.Pop());
	}
}
TEST(Stack, can_assign_stacks_of_equal_size)
{
	Stack<int> st(5);
	Stack<int> stack(5);
	for (int i = 0; i < 5; i++) {
		st.Push(i);
		stack.Push(i - 1);
	}
	EXPECT_NE(st, stack);
}
TEST(Stack, can_assign_stacks_of_different_size)
{
	Stack<int> st(5);
	Stack<int> stack(7);
	for (int i = 0; i < 7; i++) {
		if (i < 5) {
		st.Push(i);
		}
		stack.Push(i - 1);
	}
	EXPECT_NE(st, stack);
}
TEST(Stack, can_assign_stack_to_itself)
{
	Stack<int> st(5);
	
	for (int i = 0; i < 5; i++) {
		st.Push(i);
		
	}
	EXPECT_EQ(st, st);
}
TEST(Stack, equal_stacks_comparison_returns_true)
{
	Stack<int> st(5);
	for (int i = 0; i < 5; i++) {
		st.Push(i);
	}

	Stack<int> stack(5);
	for (int i = 0; i < 5; i++) {
		stack.Push(i);
	}

	EXPECT_FALSE(st != stack);
	EXPECT_TRUE(st == stack);

}
TEST(Stack, unequal_stacks_comparison_returns_false) 
{
	Stack<int> st(5);
	for (int i = 0; i < 5; i++) {
		st.Push(i);
	}

	Stack<int> stack(5);
	for (int i = 0; i < 5; i++) {
		stack.Push(1);
	}

	EXPECT_FALSE(st==stack);
	EXPECT_TRUE(st != stack);
}
TEST(Stack, empty_full_correctness)
{
	Stack<int> s(5);
	Stack<int> s1(5);
	Stack<int> s2(5);
	Stack<int> s3(5);
	for (int i = 0; i < 5; i++) {
		s1.Push(1);
	}
	s2 = s1;
	EXPECT_TRUE(s.IsEmpty());
	EXPECT_FALSE(s1.IsEmpty());
	EXPECT_TRUE(s2.IsFull());
	EXPECT_FALSE(s3.IsFull());
}
TEST(Stack, can_clear)
{
	Stack<int> stack(5);
	for (int i = 0; i < 5; i++) {
		stack.Push(1);
	}
	ASSERT_NO_THROW(stack.Clear());
}
TEST(Stack, can_pop_push_top)
{
	Stack<int> st(5);
	int smt = 10,pop;
	ASSERT_NO_THROW(st.Push(smt));
	ASSERT_NO_THROW(pop = st.Pop());
	st.Push(smt);
	ASSERT_NO_THROW(st.Top());
	EXPECT_EQ(st.Top(), smt);
	pop = st.Pop();
	EXPECT_EQ(pop, smt);
	
}
TEST(Stack, cant_pop_top_empty_and_push_full)
{
	Stack<int> st(5);
	ASSERT_ANY_THROW(st.Pop());
	ASSERT_ANY_THROW(st.Top());
	for (int i = 0; i < 5; i++) {
		st.Push(1);
	}
	ASSERT_ANY_THROW(st.Push(1));
}