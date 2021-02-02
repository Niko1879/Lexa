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
		};


		enum class Operation
		{
			Plus,
			Minus,
			Times,
			Divide,
			Raise,
		};


		const std::unordered_map<std::string, Operation> Operations
		{
			{"+", Operation::Plus},
			{"-", Operation::Minus},
			{"*", Operation::Times},
			{"/", Operation::Divide},
			{"^", Operation::Raise},
		};


		const std::unordered_map<TokenType, std::string> TokenTypeStr
		{
			{TokenType::Number, "Number"},
			{TokenType::Operation, "Operation"},
			{TokenType::LeftBracket, "LeftBracket"},
			{TokenType::RightBracket, "RightBracket"},
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

