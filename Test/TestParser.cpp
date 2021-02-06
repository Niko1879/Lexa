#include "pch.h"
#include "InterpreterTestDefs.h"
#include "Parser.h"


namespace InterpreterTest
{
	TEST(TestParser, TestParse)
	{
		std::vector<Tok> tokens = {
			Tok{Type::Number, "1"},
			Tok{Type::BinaryOperation, "+"},
			Tok{Type::Number, "3"},
			Tok{Type::BinaryOperation, "-"},
			Tok{Type::Number, "5"},
			Tok{Type::BinaryOperation, "^"},
			Tok{Type::Number, "2"},
			Tok{Type::BinaryOperation, "/"},
			Tok{Type::Number, "4"},
		};

		PTree l1(Tok{ Type::Number, "1" });
		PTree l2(Tok{ Type::Number, "3" });
		PTree p1(Tok{ Type::BinaryOperation, "+" }, std::move(l1), std::move(l2));
		PTree l3(Tok{ Type::Number, "5" });
		PTree l4(Tok{ Type::Number, "2" });
		PTree l5(Tok{ Type::Number, "4" });
		PTree t1(Tok{ Type::BinaryOperation, "^" }, std::move(l3), std::move(l4));
		PTree p2(Tok{ Type::BinaryOperation, "/" }, std::move(t1), std::move(l5));
		PTree root(Tok{ Type::BinaryOperation, "-" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseParenthesised)
	{
		std::vector<Tok> tokens = {
		   Tok{Type::LeftBracket, "("},
		   Tok{Type::Number, "4"},
		   Tok{Type::BinaryOperation, "-"},
		   Tok{Type::Number, "3"},
		   Tok{Type::RightBracket, ")"},
		   Tok{Type::BinaryOperation, "^"},
		   Tok{Type::Number, "3"},
		   Tok{Type::BinaryOperation, "/"},
		   Tok{Type::LeftBracket, "("},
		   Tok{Type::Number, "1"},
		   Tok{Type::BinaryOperation, "+"},
		   Tok{Type::Number, "3"},
		   Tok{Type::RightBracket, ")"},
		};

		PTree l1(Tok{ Type::Number, "4" });
		PTree r1(Tok{ Type::Number, "3" });
		PTree t1(Tok{ Type::BinaryOperation, "-" }, std::move(l1), std::move(r1));
		PTree t2(Tok{ Type::Number, "3" });
		PTree p1(Tok{ Type::BinaryOperation, "^" }, std::move(t1), std::move(t2));
		
		PTree l2(Tok{ Type::Number, "1" });
		PTree r2(Tok{ Type::Number, "3" });
		PTree p2(Tok{ Type::BinaryOperation, "+" }, std::move(l2), std::move(r2));
		PTree root(Tok{ Type::BinaryOperation, "/" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseVariable)
	{
		std::vector<Tok> tokens = {
			Tok{Type::Number, "2"},
			Tok{Type::BinaryOperation, "*"},
			Tok{Type::Variable, "x"},
			Tok{Type::BinaryOperation, "+"},
			Tok{Type::Number, "4"},
			Tok{Type::BinaryOperation, "-"},
			Tok{Type::Variable, "y"},
			Tok{Type::BinaryOperation, "^"},
			Tok{Type::Number, "3"},
		};

		PTree l1(Tok{ Type::Number, "2" });
		PTree r1(Tok{ Type::Variable, "x" });
		PTree t1(Tok{ Type::BinaryOperation, "*" }, std::move(l1), std::move(r1));
		PTree t2(Tok{ Type::Number, "4" });
		PTree p1(Tok{ Type::BinaryOperation, "+" }, std::move(t1), std::move(t2));

		PTree l2(Tok{ Type::Variable, "y" });
		PTree r2(Tok{ Type::Number, "3" });
		PTree p2(Tok{ Type::BinaryOperation, "^" }, std::move(l2), std::move(r2));
		PTree root(Tok{ Type::BinaryOperation, "-" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseFunction)
	{
		std::vector<Tok> tokens = {
			Tok{Type::Number, "3"},
			Tok{Type::BinaryOperation, "*"},
			Tok{Type::Function, "cos"},
			Tok{Type::LeftBracket, "("},
			Tok{Type::Variable, "x"},
			Tok{Type::RightBracket, ")"},
			Tok{Type::BinaryOperation, "+"},
			Tok{Type::Function, "sin"},
			Tok{Type::LeftBracket, "("},
			Tok{Type::Variable, "y"},
			Tok{Type::RightBracket, ")"},
		};

		PTree arg1(Tok{ Type::Variable, "x" });
		PTree l1(Tok{ Type::Number, "3" });
		PTree r1(Tok{ Type::Function, "cos" }, std::move(arg1), true);
		PTree p1(Tok{ Type::BinaryOperation, "*" }, std::move(l1), std::move(r1));

		PTree arg2(Tok{ Type::Variable, "y" });
		PTree p2(Tok{ Type::Function, "sin" }, std::move(arg2), true);
		PTree root(Tok{ Type::BinaryOperation, "+" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestParseMathConstant)
	{
		std::vector<Tok> tokens = {
			Tok{Type::MathConstant, "e"},
			Tok{Type::BinaryOperation, "^"},
			Tok{Type::Variable, "x"},
			Tok{Type::BinaryOperation, "+"},
			Tok{Type::MathConstant, "pi"},
		};

		PTree l1(Tok{ Type::MathConstant, "e" });
		PTree r1(Tok{ Type::Variable, "x" });
		PTree p1(Tok{ Type::BinaryOperation, "^" }, std::move(l1), std::move(r1));
		PTree p2(Tok{ Type::MathConstant, "pi" });
		PTree root(Tok{ Type::BinaryOperation, "+" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestNegativeNumbers)
	{
		std::vector<Tok> tokens = {
			Tok{Type::BinaryOperation, "-"},
			Tok{Type::Number, "1"},
			Tok{Type::BinaryOperation, "^"},
			Tok{Type::Number, "2"},
		};

		PTree p1(Tok{ Type::Number, "-1" });
		PTree p2(Tok{ Type::Number, "2" });
		PTree root(Tok{ Type::BinaryOperation, "^" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestNegativeNumbers2)
	{
		std::vector<Tok> tokens = {
			Tok{Type::BinaryOperation, "-"},
			Tok{Type::LeftBracket, "("},
			Tok{Type::Number, "1"},
			Tok{Type::BinaryOperation, "+"},
			Tok{Type::Number, "3"},
			Tok{Type::RightBracket, ")"},
			Tok{Type::BinaryOperation, "^"},
			Tok{Type::Number, "2"},
		};

		PTree l1(Tok{ Type::Number, "1" });
		PTree r1(Tok{ Type::Number, "3" });
		PTree p1(Tok{ Type::BinaryOperation, "+" }, std::move(l1), std::move(r1));
		PTree p2(Tok{ Type::Number, "2" });
		PTree t1(Tok{ Type::Number, "0" });
		PTree t2(Tok{ Type::BinaryOperation, "^" }, std::move(p1), std::move(p2));
		PTree root(Tok{ Type::BinaryOperation, "-" }, std::move(t1), std::move(t2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}


	TEST(TestParser, TestThrowsOnInvalid)
	{
		std::vector<Tok> tokens = {
			Tok{Type::Number, "1"},
			Tok{Type::BinaryOperation, "*"},
			Tok{Type::BinaryOperation, "/"},
			Tok{Type::Number, "1"},
		};

		EXPECT_THROW(Lexa::Interpreter::Parse(tokens), std::invalid_argument);
	}


	TEST(TestParser, TestThrowsOnInvalid2)
	{
		std::vector<Tok> tokens = {
			Tok{Type::LeftBracket, "("},
			Tok{Type::Number, "1"},
			Tok{Type::BinaryOperation, "/"},
			Tok{Type::Number, "1"},
		};

		EXPECT_THROW(Lexa::Interpreter::Parse(tokens), std::invalid_argument);
	}


	TEST(TestParser, TestThrowsOnInvalid3)
	{
		std::vector<Tok> tokens = {
			Tok{Type::RightBracket, "("},
			Tok{Type::Variable, "x"},
			Tok{Type::Variable, "y"},
		};

		EXPECT_THROW(Lexa::Interpreter::Parse(tokens), std::invalid_argument);
	}
}