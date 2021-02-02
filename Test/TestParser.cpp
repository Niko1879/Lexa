#include "pch.h"
#include "InterpreterTestDefs.h"
#include "Parser.h"


namespace InterpreterTest
{
	TEST(TestParser, TestParse)
	{
		std::vector<Tok> tokens = {
			Tok{Type::Number, "1"},
			Tok{Type::Operation, "+"},
			Tok{Type::Number, "3"},
			Tok{Type::Operation, "-"},
			Tok{Type::Number, "5"},
			Tok{Type::Operation, "^"},
			Tok{Type::Number, "2"},
			Tok{Type::Operation, "/"},
			Tok{Type::Number, "4"},
		};

		Lexa::Tree<Tok> l1(Tok{ Type::Number, "1" });
		Lexa::Tree<Tok> l2(Tok{ Type::Number, "3" });
		Lexa::Tree<Tok> p1(Tok{ Type::Operation, "+" }, std::move(l1), std::move(l2));
		Lexa::Tree<Tok> l3(Tok{ Type::Number, "5" });
		Lexa::Tree<Tok> l4(Tok{ Type::Number, "2" });
		Lexa::Tree<Tok> l5(Tok{ Type::Number, "4" });
		Lexa::Tree<Tok> t1(Tok{ Type::Operation, "^" }, std::move(l3), std::move(l4));
		Lexa::Tree<Tok> p2(Tok{ Type::Operation, "/" }, std::move(t1), std::move(l5));
		Lexa::Tree<Tok> root(Tok{ Type::Operation, "-" }, std::move(p1), std::move(p2));

		EXPECT_NO_THROW(Lexa::Interpreter::Parse(tokens));
		EXPECT_EQ(root, Lexa::Interpreter::Parse(tokens));
	}
}