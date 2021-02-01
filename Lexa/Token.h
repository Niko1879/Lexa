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
		};


		const std::unordered_map<TokenType, std::string> TokenTypeStr
		{
			{TokenType::Number, "Number"},
			{TokenType::Operation, "Operation"},
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

