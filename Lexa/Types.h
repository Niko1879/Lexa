#pragma once
#include <unordered_map>


namespace Lexa
{
	namespace Interpreter
	{
		using Number = float;
		using Variable = std::string;


		enum class TokenType
		{
			Number,
			BinaryOperation,
			LeftBracket,
			RightBracket,
			Variable,
			Function,
			MathConstant,
		};


		const std::unordered_map<TokenType, std::string> TokenTypeToStr
		{
			{TokenType::Number, "Number"},
			{TokenType::BinaryOperation, "BinaryOperation"},
			{TokenType::LeftBracket, "LeftBracket"},
			{TokenType::RightBracket, "RightBracket"},
			{TokenType::Variable, "Variable"},
			{TokenType::Function, "Function"},
		};


		using BinaryOperation = float(*)(float, float);
		const std::unordered_map<std::string, BinaryOperation> StrToBinaryOperation
		{
			{"+", [](float a, float b) {return a + b; } },
			{"-", [](float a, float b) {return a - b; } },
			{"*",[](float a, float b) {return a * b; } },
			{"/", [](float a, float b) {return a / b; } },
			{"^", pow},
		};


		const std::unordered_map<std::string, int> OperatorPrecedence
		{
			{"-", 0},
			{"+", 0},
			{"*", 1},
			{"/", 1},
			{"^", 2},
		};


		using Function = float(*)(float);
		const std::unordered_map<std::string, Function> StrToFunction
		{
			{"sqrt", sqrt},
			{"exp", exp},
			{"log", log},
			{"ln", log},
			{"sin", sin},
			{"cos", cos},
			{"tan", tan},
			{"sec", [](float a) {return 1/cos(a); }},
			{"cosec", [](float a) {return 1 / sin(a); }},
			{"cot", [](float a) {return 1 / tan(a); }},
			{"sinh", sinh},
			{"cosh", cosh},
			{"tanh", tanh},
			{"sech", [](float a) {return 1 / cosh(a); }},
			{"cosech", [](float a) {return 1 / sinh(a); }},
			{"coth", [](float a) {return 1 / tanh(a); }},
			{"arcsin", asin},
			{"arccos", acos},
			{"arctan", atan},
			{"arcsec", [](float a) {return acos(1 / a); }},
			{"arccosec", [](float a) {return asin(1 / a); }},
			{"arccot", [](float a) {return atan(1 / a); }},
			{"arsinh", asinh},
			{"arcosh", acosh},
			{"artanh", atanh},
			{"arsech", [](float a) {return acosh(1 / a); }},
			{"arcosech", [](float a) {return asinh(1 / a); }},
			{"artanh", [](float a) {return atanh(1 / a); }},
		};


		const std::unordered_map<std::string, float> StrToMathConstant
		{
			{"e", exp(1.0f)},
			{"pi", atan(1.0f) * 4},
		};
	}
}