#include "Lexer.h"

namespace Lexa
{
	namespace Interpreter
	{		
		std::vector<Token> Tokenise(const std::string& expression)
		{
			std::vector<Token> tokens;

			std::stringstream numbuf;
			for (size_t i = 0; i < expression.size(); ++i)
			{
				char curr = expression[i];
				std::string curr_s = std::string(1, curr);
				
				if (isdigit(curr))
				{
					numbuf << curr;
					continue;
				}

				if (numbuf.str().size() > 0)
				{
					tokens.push_back(Token{ TokenType::Number, numbuf.str() });
					numbuf.str("");
					numbuf.clear();
				}

				if (Operations.find(curr_s) != Operations.end())
					tokens.push_back(Token{ TokenType::Operation, curr_s });

				else if (isspace(curr))
					continue;

				else throw std::invalid_argument("Unidentified token: " + curr_s);
			}

			if (numbuf.str().size() > 0)
				tokens.push_back(Token{ TokenType::Number, numbuf.str() });

			return tokens;
		}
	}
}