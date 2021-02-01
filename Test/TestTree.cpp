#include "pch.h"
#include "InterpreterTestDefs.h"


namespace InterpreterTest
{
	TEST(TestTree, TestConstruct)
	{
		Tok t{ Type::Number, "1" };
		EXPECT_NO_THROW(
			Lexa::Tree<Tok> left(Tok{ Type::Number, "1" });
			Lexa::Tree<Tok> right(t);
			Lexa::Tree<Tok> root(Tok{Type::Operation, "+"}, std::move(left), std::move(right));
		);
	}

	TEST(TestTree, TestGetData)
	{
		Tok t{ Type::Number, "1" };
		Tok u{ Type::Number, "1" };
		Lexa::Tree<Tok> root(t);
		EXPECT_EQ(root.Data(), t);
		root.Data() = u;
		EXPECT_EQ(root.Data(), u);
	}
}