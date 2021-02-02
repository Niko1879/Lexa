#pragma once
#include <unordered_map>
#include <ostream>

namespace Lexa
{
	namespace Interpreter
	{
		enum class TokenType
		{
			Number,
			Operation,
			LeftBracket,
			RightBracket,
			Variable,
			Function,
		};


		enum class Operation
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


		const std::unordered_map<std::string, Operation> StrToOperation
		{
			{"+", Operation::Plus},
			{"-", Operation::Minus},
			{"*", Operation::Times},
			{"/", Operation::Divide},
			{"^", Operation::Raise},
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


		const std::unordered_map<TokenType, std::string> StrToTokenType
		{
			{TokenType::Number, "Number"},
			{TokenType::Operation, "Operation"},
			{TokenType::LeftBracket, "LeftBracket"},
			{TokenType::RightBracket, "RightBracket"},
			{TokenType::Variable, "Variable"},
			{TokenType::Function, "Function"},
		};


		struct Token
		{
			TokenType type;
			std::string value;
		};


		bool operator==(const Token& t1, const Token& t2);
		std::ostream& operator<<(std::ostream& stream, const Token& token);
	}
};

