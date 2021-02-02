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

		Lexa::Tree<Tok> l1(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> l2(Tok{ Type::Number, "3" });
		Lexa::Tree<Tok> p1(Tok{ Type::BinaryOperation, "+" }, std::move(l1), std::move(l2));
		Lexa::Tree<Tok> l3(Tok{ Type::Number, "5" });
		Lexa::Tree<Tok> l4(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> l5(Tok{ Type::Number, "4" });
		Lexa::Tree<Tok> t1(Tok{ Type::BinaryOperation, "^" }, std::move(l3), std::move(l4));
		Lexa::Tree<Tok> p2(Tok{ Type::BinaryOperation, "/" }, std::move(t1), std::move(l5));
		Lexa::Tree<Tok> root(Tok{ Type::BinaryOperation, "-" }, std::move(p1), std::move(p2));

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

		Lexa::Tree<Tok> l1(Tok{ Type::Number, "4" });
		Lexa::Tree<Tok> r1(Tok{ Type::Number, "3" });
		Lexa::Tree<Tok> t1(Tok{ Type::BinaryOperation, "-" }, std::move(l1), std::move(r1));
		Lexa::Tree<Tok> t2(Tok{ Type::Number, "3" });
		Lexa::Tree<Tok> p1(Tok{ Type::BinaryOperation, "^" }, std::move(t1), std::move(t2));
		
		Lexa::Tree<Tok> l2(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> r2(Tok{ Type::Number, "3" });
		Lexa::Tree<Tok> p2(Tok{ Type::BinaryOperation, "+" }, std::move(l2), std::move(r2));
		Lexa::Tree<Tok> root(Tok{ Type::BinaryOperation, "/" }, std::move(p1), std::move(p2));

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

		Lexa::Tree<Tok> l1(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> r1(Tok{ Type::Variable, "x" });
		Lexa::Tree<Tok> t1(Tok{ Type::BinaryOperation, "*" }, std::move(l1), std::move(r1));
		Lexa::Tree<Tok> t2(Tok{ Type::Number, "4" });
		Lexa::Tree<Tok> p1(Tok{ Type::BinaryOperation, "+" }, std::move(t1), std::move(t2));

		Lexa::Tree<Tok> l2(Tok{ Type::Variable, "y" });
		Lexa::Tree<Tok> r2(Tok{ Type::Number, "3" });
		Lexa::Tree<Tok> p2(Tok{ Type::BinaryOperation, "^" }, std::move(l2), std::move(r2));
		Lexa::Tree<Tok> root(Tok{ Type::BinaryOperation, "-" }, std::move(p1), std::move(p2));

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

		Lexa::Tree<Tok> arg1(Tok{ Type::Variable, "x" });
		Lexa::Tree<Tok> l1(Tok{ Type::Number, "3" });
		Lexa::Tree<Tok> r1(Tok{ Type::Function, "cos" }, std::move(arg1), true);
		Lexa::Tree<Tok> p1(Tok{ Type::BinaryOperation, "*" }, std::move(l1), std::move(r1));

		Lexa::Tree<Tok> arg2(Tok{ Type::Variable, "y" });
		Lexa::Tree<Tok> p2(Tok{ Type::Function, "sin" }, std::move(arg2), true);
		Lexa::Tree<Tok> root(Tok{ Type::BinaryOperation, "+" }, std::move(p1), std::move(p2));

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

		Lexa::Tree<Tok> l1(Tok{ Type::MathConstant, "e" });
		Lexa::Tree<Tok> r1(Tok{ Type::Variable, "x" });
		Lexa::Tree<Tok> p1(Tok{ Type::BinaryOperation, "^" }, std::move(l1), std::move(r1));
		Lexa::Tree<Tok> p2(Tok{ Type::MathConstant, "pi" });
		Lexa::Tree<Tok> root(Tok{ Type::BinaryOperation, "+" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}
}