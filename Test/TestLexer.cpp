#include "pch.h"
#include "InterpreterTestDefs.h"
#include "Lexer.h"


namespace InterpreterTest
{
    TEST(TestLexer, TestTokenise)
    {
        std::vector<Tok> actual;
        EXPECT_NO_THROW(actual = Lexa::Interpreter::Tokenise("1 + 1 -2*3/ 4^2"));
        std::vector<Tok> expected = {
            Tok{Type::Number, "1"},
            Tok{Type::Operation, "+"},
            Tok{Type::Number, "1"},
            Tok{Type::Operation, "-"},
            Tok{Type::Number, "2"},
            Tok{Type::Operation, "*"},
            Tok{Type::Number, "3"},
            Tok{Type::Operation, "/"},
            Tok{Type::Number, "4"},
            Tok{Type::Operation, "^"},
            Tok{Type::Number, "2"},
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokeniseThrowsOnInvalid)
    {
        EXPECT_THROW(Lexa::Interpreter::Tokenise("aod2c/*`=02@#-=\"!£^*&\`\"\"£&*\"(%%)!\""), std::invalid_argument);
    }


    TEST(TestLexer, TestTokeniseParen)
    {
        std::vector<Tok> actual;
        EXPECT_NO_THROW(actual = Lexa::Interpreter::Tokenise("(4 - 3)^3/(1 + 3)"));
        std::vector<Tok> expected = {
            Tok{Type::LeftBracket, "("},
            Tok{Type::Number, "4"},
            Tok{Type::Operation, "-"},
            Tok{Type::Number, "3"},
            Tok{Type::RightBracket, ")"},
            Tok{Type::Operation, "^"},
            Tok{Type::Number, "3"},
            Tok{Type::Operation, "/"},
            Tok{Type::LeftBracket, "("},
            Tok{Type::Number, "1"},
            Tok{Type::Operation, "+"},
            Tok{Type::Number, "3"},
            Tok{Type::RightBracket, ")"},
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokeniseVariable)
    {
        std::vector<Tok> actual;
        EXPECT_NO_THROW(actual = Lexa::Interpreter::Tokenise("2*x + 4 - y^3"));
        std::vector<Tok> expected = {
            Tok{Type::Number, "2"},
            Tok{Type::Operation, "*"},
            Tok{Type::Variable, "x"},
            Tok{Type::Operation, "+"},
            Tok{Type::Number, "4"},
            Tok{Type::Operation, "-"},
            Tok{Type::Variable, "y"},
            Tok{Type::Operation, "^"},
            Tok{Type::Number, "3"},
        };

        EXPECT_EQ(expected, actual);
    }
}