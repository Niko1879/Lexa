#include "pch.h"
#include "InterpreterTestDefs.h"
#include "Tree.h"

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


	TEST(TestTree, TestGetChild)
	{
		Lexa::Tree<Tok> left(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> right(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> root(Tok{ Type::Operation, "+" }, std::move(left), std::move(right));

		Lexa::Tree<Tok>& l = root.Left();
		Lexa::Tree<Tok>& r = root.Right();

		Tok c1{ Type::Number, "1" };
		Tok c2{ Type::Number, "2" };
		EXPECT_EQ(l.Data(), c1);
		EXPECT_EQ(r.Data(), c2);
	}


	TEST(TestTree, TestEqualityTrue)
	{
		Lexa::Tree<Tok> l1(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> r1(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> t1(Tok{ Type::Operation, "+" }, std::move(l1), std::move(r1));

		Lexa::Tree<Tok> l2(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> r2(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> t2(Tok{ Type::Operation, "+" }, std::move(l2), std::move(r2));

		EXPECT_TRUE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse1)
	{
		Lexa::Tree<Tok> l1(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> r1(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> t1(Tok{ Type::Operation, "+" }, std::move(l1), std::move(r1));

		Lexa::Tree<Tok> l2(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> r2(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> t2(Tok{ Type::Operation, "+" }, std::move(l2), std::move(r2));

		EXPECT_FALSE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse2)
	{
		Lexa::Tree<Tok> l1(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> r1(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> t1(Tok{ Type::Operation, "-" }, std::move(l1), std::move(r1));

		Lexa::Tree<Tok> l2(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> r2(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> t2(Tok{ Type::Operation, "+" }, std::move(l2), std::move(r2));

		EXPECT_FALSE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse3)
	{
		Lexa::Tree<Tok> l1(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> t1(Tok{ Type::Operation, "+" }, std::move(l1), true);

		Lexa::Tree<Tok> l2(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> r2(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> t2(Tok{ Type::Operation, "+" }, std::move(l1), std::move(r2));

		EXPECT_FALSE(t1 == t2);
	}
}