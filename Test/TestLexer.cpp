#include "pch.h"
#include "InterpreterTestDefs.h"


namespace InterpreterTest
{
    using Tok = Lexa::Interpreter::Token;
    using Type = Lexa::Interpreter::TokenType;

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
}