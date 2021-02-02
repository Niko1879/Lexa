#pragma once
#include <unordered_map>


namespace Lexa
{
	namespace Interpreter
	{
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


		enum class BinaryOperation
		{
			Plus,
			Minus,
			Times,
			Divide,
			Raise,
		};


		enum class Function
		{
			Exp,
			Log,
			Sin,
			Cos,
			Tan,
			Sec,
			Cosec,
			Cot,
			Sinh,
			Cosh,
			Tanh,
			Sech,
			Cosech,
			Coth,
			Arcsin,
			Arccos,
			Arctan,
			Arcsec,
			Arccosec,
			Arccot,
			Arsinh,
			Arcosh,
			Artanh,
			Arsech,
			Arcosech,
			Arcoth,
		};


		enum class MathConstant
		{
			E,
			Pi,
		};


		const std::unordered_map<TokenType, std::string> StrToTokenType
		{
			{TokenType::Number, "Number"},
			{TokenType::BinaryOperation, "BinaryOperation"},
			{TokenType::LeftBracket, "LeftBracket"},
			{TokenType::RightBracket, "RightBracket"},
			{TokenType::Variable, "Variable"},
			{TokenType::Function, "Function"},
		};


		const std::unordered_map<std::string, BinaryOperation> StrToBinaryOperation
		{
			{"+", BinaryOperation::Plus},
			{"-", BinaryOperation::Minus},
			{"*", BinaryOperation::Times},
			{"/", BinaryOperation::Divide},
			{"^", BinaryOperation::Raise},
		};


		const std::unordered_map<std::string, Function> StrToFunction
		{
			{"exp", Function::Exp},
			{"log", Function::Log},
			{"ln", Function::Log},
			{"sin", Function::Sin},
			{"cos", Function::Cos},
			{"tan", Function::Tan},
			{"sec", Function::Sec},
			{"cosec", Function::Cosec},
			{"cot", Function::Cot},
			{"sinh", Function::Sinh},
			{"cosh", Function::Cosh},
			{"tanh", Function::Tanh},
			{"sech", Function::Sech},
			{"cosech", Function::Cosech},
			{"coth", Function::Coth},
			{"arcsin", Function::Arcsin},
			{"arccos", Function::Arccos},
			{"arctan", Function::Arctan},
			{"arcsec", Function::Arcsec},
			{"arccosec", Function::Arccosec},
			{"arccot", Function::Arccot},
			{"arsinh", Function::Arsinh},
			{"arcosh", Function::Arcosh},
			{"artanh", Function::Artanh},
			{"arsech", Function::Arsech},
			{"arcosech", Function::Arcosech},
			{"artanh", Function::Artanh},
		};


		const std::unordered_map<std::string, MathConstant> StrToMathConstant
		{
			{"e", MathConstant::E},
			{"pi", MathConstant::Pi},
		};


		const std::unordered_map<BinaryOperation, int> OperatorPrecedence
		{
			{BinaryOperation::Plus, 0},
			{BinaryOperation::Minus, 0},
			{BinaryOperation::Times, 1},
			{BinaryOperation::Divide, 1},
			{BinaryOperation::Raise, 2},
		};
	}
}