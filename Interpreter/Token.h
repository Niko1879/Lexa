#pragma once
#include <unordered_map>
#include <ostream>


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

	struct Token
	{
		TokenType type;
		std::string value;
	};


	bool operator==(const Token& t1, const Token& t2);
	std::ostream& operator<<(std::ostream& stream, const Token& token);
}

