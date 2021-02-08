#include "pch.h"
#include "InterpreterTestDefs.h"
#include "Lexer.h"
#include "Parser.h"
#include "Eval.h"


namespace InterpreterTests
{
	const float x = 2.5f;
	const float y = -1.2f;
	
	const std::unordered_map<std::string, float> testCases = {
		{"(x + y)^3", 2.197f},
		{"2x + y", 3.8f},
		{"sin(x^2 + y^2)", 0.986585f},
		{"3/(1 + 2x + y)", 0.625f},
		{"(1+x)(1-y)^(-1)", 1.59091f},
		{"sin(cos(tan(xy)))", 0.835947745218015562670704049f},
		{"3arcsec(x)coth(y)", -4.17180f},
		{"-xyxyxy", 27.0f},
		{"27.49x^3/y", -357.943f},
		{"1/(1 + 1/(x + y))", 0.565217f},
		{"x^2y^2", 9.0f},
		{"x^(x^y)", 1.35682f},
		{"e^xtan(pi*y)", -8.8511f},
		{"x - (-ycos(-x/4))", 1.52684f},
		{"sqrt(1 - log(-xy/2))", 0.771061f},
		{"(x + y)/0", NAN},
	};


	TEST(TestInterpreter, TestCases)
	{
		for (const auto& pair : testCases)
		{
			auto expr = pair.first;
			std::cout << expr << std::endl;
			auto expected = pair.second;
			EXPECT_NO_THROW(Interpreter::Tokenise(pair.first));
			auto tokens = Interpreter::Tokenise(pair.first);
			EXPECT_NO_THROW(Interpreter::Parse(tokens));
			auto pTree = Interpreter::Parse(tokens);
			EXPECT_NO_THROW(Interpreter::Eval2D _(pTree));
			auto eval = Interpreter::Eval2D(pTree);
			EXPECT_NO_THROW(eval(x, y));
			float res = eval(x, y);
			if (!FLOAT_EQ(res, expected) && !isnan(res))
			{
				EXPECT_EQ(res, expected);
			}
		}
	}
}