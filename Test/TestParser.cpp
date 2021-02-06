#include "pch.h"
#include "InterpreterTestDefs.h"
#include "Parser.h"


namespace InterpreterTest
{
	TEST(TestParser, TestParse)
	{
		TOKENS tokens = {
			NUM("1"), OP("+"), NUM("3"), OP("-"), NUM("5"),
			OP("^"), NUM("2"), OP("/"), NUM("4")
		};

		LEAF(l1, NUM("1"));
		LEAF(l2, NUM("3"));
		BRANCH(p1, OP("+"), l1, l2);
		LEAF(l3, NUM("5"));
		LEAF(l4, NUM("2"));
		LEAF(l5, NUM("4"));
		BRANCH(t1, OP("^"), l3, l4);
		BRANCH(p2, OP("/"), t1, l5);
		BRANCH(root, OP("-"), p1, p2);

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseParenthesised)
	{
		TOKENS tokens = {
		   LBRACKET, NUM("4"), OP("-"), NUM("3"), RBRACKET, OP("^"),
		   NUM("3"), OP("/"), LBRACKET, NUM("1"), OP("+"), NUM("3"),
		   RBRACKET
		};

		LEAF(l1, NUM("4"));
		LEAF(r1, NUM("3"));
		BRANCH(t1, OP("-"), l1, r1);
		LEAF(t2, NUM("3"));
		BRANCH(p1, OP("^"), t1, t2);
		LEAF(l2, NUM("1"));
		LEAF(r2, NUM("3"));
		BRANCH(p2, OP("+"), l2, r2);
		BRANCH(root, OP("/"), p1, p2);

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseVariable)
	{
		TOKENS tokens = {
			NUM("2"), OP("*"), VAR("x"), OP("+"), NUM("4"),
			OP("-"), VAR("y"), OP("^"), NUM("3")
		};

		LEAF(l1, NUM("2"));
		LEAF(r1, VAR("x"));
		BRANCH(t1, OP("*"), l1, r1);
		LEAF(t2, NUM("4"));
		BRANCH(p1, OP("+"), t1, t2);
		LEAF(l2, VAR("y"));
		LEAF(r2, NUM("3"));
		BRANCH(p2, OP("^"), l2, r2);
		BRANCH(root, OP("-"), p1, p2);

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseFunction)
	{
		TOKENS tokens = {
			NUM("3"), OP("*"), FUN("cos"), LBRACKET, VAR("x"), RBRACKET,
			OP("+"), FUN("sin"), LBRACKET, VAR("y"), RBRACKET
		};

		LEAF(arg1, VAR("x"));
		LEAF(l1, NUM("3"));
		BRANCH(r1, FUN("cos"), arg1, true);
		BRANCH(p1, OP("*"), l1, r1);
		LEAF(arg2, VAR("y"));
		BRANCH(p2, FUN("sin"), arg2, true);
		BRANCH(root, OP("+"), p1, p2);

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseMathConstant)
	{
		TOKENS tokens = {
			MCON("e"), OP("^"), VAR("x"), OP("+"), MCON("pi")
		};

		LEAF(l1, MCON("e"));
		LEAF(r1, VAR("x"));
		BRANCH(p1, OP("^"), l1, r1);
		LEAF(p2, MCON("pi"));
		BRANCH(root, OP("+"), p1, p2);

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestNegativeNumbers)
	{
		TOKENS tokens = {
			OP("-"), NUM("1"), OP("^"), NUM("2")
		};

		LEAF(l1, NUM("1"));
		LEAF(r1, NUM("2"));
		LEAF(p1, NUM("0"));
		BRANCH(p2, OP("^"), l1, r1);
		BRANCH(root, OP("-"), p1, p2);

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestNegativeNumbers2)
	{
		TOKENS tokens = {
			OP("-"), LBRACKET, NUM("1"), OP("+"),
			NUM("3"), RBRACKET, OP("^"), NUM("2")
		};

		LEAF(l1, NUM("1"));
		LEAF(r1, NUM("3"));
		BRANCH(p1, OP("+"), l1, r1);
		LEAF(p2, NUM("2"));
		LEAF(t1, NUM("0"));
		BRANCH(t2, OP("^"), p1, p2);
		BRANCH(root, OP("-"), t1, t2);

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestThrowsOnInvalid)
	{
		TOKENS tokens = {
			NUM("1"), OP("*"), OP("/"), NUM("1")
		};

		EXPECT_THROW(Lexa::Interpreter::Parse(tokens), std::invalid_argument);
	}


	TEST(TestParser, TestThrowsOnInvalid2)
	{
		TOKENS tokens = {
			LBRACKET, NUM("1"), OP("/"), NUM("1")
		};

		EXPECT_THROW(Lexa::Interpreter::Parse(tokens), std::invalid_argument);
	}


	TEST(TestParser, TestThrowsOnInvalid3)
	{
		TOKENS tokens = {
			RBRACKET, VAR("x"), VAR("y")
		};

		EXPECT_THROW(Lexa::Interpreter::Parse(tokens), std::invalid_argument);
	}
}