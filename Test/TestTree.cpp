#include "pch.h"
#include "InterpreterTestDefs.h"


namespace InterpreterTest
{
	TEST(TestTree, TestConstruct)
	{
		EXPECT_NO_THROW(
			Lexa::Tree<Tok> left(Tok{ Type::Number, "1" });
			Lexa::Tree<Tok> right(Tok{ Type::Number, "1" });
			Lexa::Tree<Tok> root(Tok{Type::Operation, "+"}, std::move(left), std::move(right));
		);
	}
}