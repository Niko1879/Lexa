#include "pch.h"
#include "InterpreterTestDefs.h"


namespace InterpreterTest
{
	TEST(TestTree, TestConstruct)
	{
		Tok t{ Type::Number, "1" };
		EXPECT_NO_THROW(
			PTree left(Tok{ Type::Number, "1" });
			PTree right(t);
			PTree root(Tok{Type::BinaryOperation, "+"}, std::move(left), std::move(right));
		);
	}

	TEST(TestTree, TestGetData)
	{
		Tok t{ Type::Number, "1" };
		Tok u{ Type::Number, "1" };
		PTree root(t);
		EXPECT_EQ(root.Data(), t);
		root.Data() = u;
		EXPECT_EQ(root.Data(), u);
	}


	TEST(TestTree, TestGetChild)
	{
		PTree left(Tok{ Type::Number, "1" });
		PTree right(Tok{ Type::Number, "2" });
		PTree root(Tok{ Type::BinaryOperation, "+" }, std::move(left), std::move(right));

		PTree& l = root.Left();
		PTree& r = root.Right();

		Tok c1{ Type::Number, "1" };
		Tok c2{ Type::Number, "2" };
		EXPECT_EQ(l.Data(), c1);
		EXPECT_EQ(r.Data(), c2);
	}


	TEST(TestTree, TestEqualityTrue)
	{
		PTree l1(Tok{ Type::Number, "1" });
		PTree r1(Tok{ Type::Number, "2" });
		PTree t1(Tok{ Type::BinaryOperation, "+" }, std::move(l1), std::move(r1));

		PTree l2(Tok{ Type::Number, "1" });
		PTree r2(Tok{ Type::Number, "2" });
		PTree t2(Tok{ Type::BinaryOperation, "+" }, std::move(l2), std::move(r2));

		EXPECT_TRUE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse1)
	{
		PTree l1(Tok{ Type::Number, "1" });
		PTree r1(Tok{ Type::Number, "2" });
		PTree t1(Tok{ Type::BinaryOperation, "+" }, std::move(l1), std::move(r1));

		PTree l2(Tok{ Type::Number, "2" });
		PTree r2(Tok{ Type::Number, "1" });
		PTree t2(Tok{ Type::BinaryOperation, "+" }, std::move(l2), std::move(r2));

		EXPECT_FALSE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse2)
	{
		PTree l1(Tok{ Type::Number, "1" });
		PTree r1(Tok{ Type::Number, "2" });
		PTree t1(Tok{ Type::BinaryOperation, "-" }, std::move(l1), std::move(r1));

		PTree l2(Tok{ Type::Number, "1" });
		PTree r2(Tok{ Type::Number, "2" });
		PTree t2(Tok{ Type::BinaryOperation, "+" }, std::move(l2), std::move(r2));

		EXPECT_FALSE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse3)
	{
		PTree l1(Tok{ Type::Number, "1" });
		PTree t1(Tok{ Type::BinaryOperation, "+" }, std::move(l1), true);

		PTree l2(Tok{ Type::Number, "1" });
		PTree r2(Tok{ Type::Number, "2" });
		PTree t2(Tok{ Type::BinaryOperation, "+" }, std::move(l1), std::move(r2));

		EXPECT_FALSE(t1 == t2);
	}
}