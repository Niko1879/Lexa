#include "Token.h"


namespace Interpreter
{
	static const std::unordered_map<TokenType, std::string> TokenTypeToStr
	{
		{TokenType::Number, "Number"},
		{TokenType::BinaryOperation, "BinaryOperation"},
		{TokenType::LeftBracket, "LeftBracket"},
		{TokenType::RightBracket, "RightBracket"},
		{TokenType::Variable, "Variable"},
		{TokenType::Function, "Function"},
	};

	bool operator==(const Token& t1, const Token& t2)
	{
		return t1.type == t2.type &&
			t1.value == t2.value;
	}


	std::ostream& operator<<(std::ostream& stream, const Token& token)
	{
		return stream << "(" << TokenTypeToStr.at(token.type) << ", " << token.value << ")";
	}
}