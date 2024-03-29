#include "pch.h"
#include "InterpreterTestDefs.h"
#include "Lexer.h"


namespace InterpreterTest
{
    TEST(TestLexer, TestTokenise)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("1 + 1 -2*3/ 4^2"));
        TOKENS expected = {
            NUM("1"), OP("+"), NUM("1"), OP("-"), NUM("2"), OP("*"), 
            NUM("3"), OP("/"), NUM("4"), OP("^"), NUM("2")
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokenise2)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("1111 + 1234 -222*333/ 401^2"));
        TOKENS expected = {
            NUM("1111"), OP("+"), NUM("1234"), OP("-"), NUM("222"),
            OP("*"), NUM("333"), OP("/"), NUM("401"), OP("^"), NUM("2")
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokeniseNegativeNumbers)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("-1"));
        TOKENS expected = { OP("-"), NUM("1") };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokeniseDecimal)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("321.334 + 5"));
        TOKENS expected = { NUM("321.334"), OP("+"), NUM("5") };

        EXPECT_EQ(expected, actual);
    }

    
    TEST(TestLexer, TestTokeniseParen)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("(4 - 3)^3/(1 + 3)"));
        TOKENS expected = {
            LBRACKET, NUM("4"), OP("-"), NUM("3"), RBRACKET, OP("^"), 
            NUM("3"), OP("/"), LBRACKET, NUM("1"), OP("+"), NUM("3"),
            RBRACKET
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokeniseVariable)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("2*x + 4 - y^3"));
        TOKENS expected = {
            NUM("2"), OP("*"), VAR("x"), OP("+"), NUM("4"),
            OP("-"), VAR("y"), OP("^"), NUM("3")
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokeniseFunction)
    {
        for (auto p : Interpreter::StrToFunction)
        {
            TOKENS actual = Interpreter::Tokenise(p.first + ("(x)"));
            TOKENS expected = {
                FUN(p.first), LBRACKET, VAR("x"), RBRACKET
            };

            EXPECT_EQ(expected, actual);
        }
    }


    TEST(TestLexer, TestTokeniseMathConstant)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("e^x + pi"));
        TOKENS expected = {
            MCON("e"), OP("^"), VAR("x"), OP("+"), MCON("pi")
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestCaseSensitivity)
    {
        TOKENS actual;
        EXPECT_NO_THROW(actual = Interpreter::Tokenise("SiN(x)coS(x)"));
        TOKENS expected = {
            FUN("sin"), LBRACKET, VAR("x"), RBRACKET, FUN("cos"),
            LBRACKET, VAR("x"), RBRACKET
        };

        EXPECT_EQ(expected, actual);
    }


    TEST(TestLexer, TestTokeniseThrowsOnInvalid)
    {
        EXPECT_THROW(Interpreter::Tokenise("aod2c/*`=02@#-=\"!�^*&\`\"\"�&*\"(%%)!\""), std::invalid_argument);
    }
}