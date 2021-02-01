#include "Lexer.h"

namespace Lexa
{
	namespace Interpreter
	{
		bool operator==(const Token& t1, const Token& t2)
		{
			return t1.type == t2.type && 
				   t1.value == t2.value;
		}
		
		
		std::vector<Token> Tokenise(const std::string& expression)
		{
			std::vector<Token> tokens;
			return tokens;
		}
	}
}