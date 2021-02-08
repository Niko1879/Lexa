#include "pch.h"
#include "InterpreterTestDefs.h"


namespace InterpreterTest
{
	TEST(TestTree, TestConstruct)
	{
		Tok t = NUM("1");
		EXPECT_NO_THROW(
			LEAF(left, NUM("1"));
			LEAF(right, t);
			BRANCH(root, OP("+"), left, right);
		);
	}

	TEST(TestTree, TestGetData)
	{
		Tok t = NUM("1");
		Tok u = NUM("2");
		LEAF(root, t);
		EXPECT_EQ(root.Data(), NUM("1"));
		root.Data() = u;
		EXPECT_EQ(root.Data(), NUM("2"));
	}


	TEST(TestTree, TestGetChild)
	{
		LEAF(left, NUM("1"));
		LEAF(right, NUM("2"));
		BRANCH(root, OP("+"), left, right);

		PTree& l = root.Left();
		PTree& r = root.Right();

		Tok c1 = NUM("1");
		Tok c2 = NUM("2");
		EXPECT_EQ(l.Data(), c1);
		EXPECT_EQ(r.Data(), c2);
	}


	TEST(TestTree, TestEqualityTrue)
	{
		LEAF(l1, NUM("1"));
		LEAF(r1, NUM("2"));
		BRANCH(t1, OP("+"), l1, r1);

		LEAF(l2, NUM("1"));
		LEAF(r2, NUM("2"));
		BRANCH(t2, OP("+"), l2, r2);

		EXPECT_TRUE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse1)
	{
		LEAF(l1, NUM("1"));
		LEAF(r1, NUM("2"));
		BRANCH(t1, OP("+"), l1, r1);

		LEAF(l2, NUM("2"));
		LEAF(r2, NUM("1"));
		BRANCH(t2, OP("+"), l2, r2);

		EXPECT_FALSE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse2)
	{
		LEAF(l1, NUM("1"));
		LEAF(r1, NUM("2"));
		BRANCH(t1, OP("-"), l1, r1);

		LEAF(l2, NUM("1"));
		LEAF(r2, NUM("2"));
		BRANCH(t2, OP("+"), l2, r2);

		EXPECT_FALSE(t1 == t2);
	}


	TEST(TestTree, TestEqualityFalse3)
	{
		LEAF(l1, NUM("1"));
		BRANCH(t1, OP("+"), l1, true);

		LEAF(l2, NUM("1"));
		LEAF(r2, NUM("2"));
		BRANCH(t2, OP("+"), l1, r2);

		EXPECT_FALSE(t1 == t2);
	}


	TEST(TestTree, TestFindUnique)
	{
		LEAF(l1, VAR("x"));
		LEAF(r1, VAR("y"));
		BRANCH(b1, OP("+"), l1, r1);

		LEAF(l2, VAR("x"));
		LEAF(r2, VAR("y"));
		BRANCH(b2, OP("-"), l2, r2);

		BRANCH(root, OP("/"), b1, b2);
		std::vector<Tok> res = Tree::FindUnique(root, [](const Tok& t) {return t.value == "x" || t.value == "y"; });

		EXPECT_EQ(res.size(), 2);
		EXPECT_EQ(res[0], VAR("x"));
		EXPECT_EQ(res[1], VAR("y"));
	}
}