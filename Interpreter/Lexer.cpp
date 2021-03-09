#include "Lexer.h"


namespace Interpreter
{		
	void _TokeniseChars(std::stringstream& charbuf, std::vector<Token>& tokens)
	{
		while (!charbuf.str().empty())
		{
			std::string chars = charbuf.str();
			charbuf.str("");
			charbuf.clear();
			if (StrToFunction.find(chars) != StrToFunction.end())
				tokens.push_back(Token{ TokenType::Function, chars });

			else if (StrToMathConstant.find(chars) != StrToMathConstant.end())
				tokens.push_back(Token{ TokenType::MathConstant, chars });

			else
			{
				char var = chars[0];
				tokens.push_back(Token{ TokenType::Variable, std::string(1, var) });
				for (size_t i = 1; i < chars.size(); ++i)
					charbuf << chars[i];
			}
		}
	}
	
	
	std::vector<Token> Tokenise(const std::string& expression)
	{
		std::vector<Token> tokens;

		std::stringstream numbuf;
		std::stringstream charbuf;
		for (size_t i = 0; i < expression.size(); ++i)
		{
			char curr = tolower(expression[i]);
			std::string curr_s = std::string(1, curr);
			
			if (isdigit(curr) || curr == '.')
			{
				numbuf << curr;
				continue;
			}

			if (isalpha(curr))
			{
				charbuf << curr;
				continue;
			}

			if (numbuf.str().size() > 0)
			{
				tokens.push_back(Token{ TokenType::Number, numbuf.str() });
				numbuf.str("");
				numbuf.clear();
			}

			if (charbuf.str().size() > 0)
			{
				_TokeniseChars(charbuf, tokens);
			}

			if (isspace(curr))
				continue;

			if (StrToBinaryOperation.find(curr_s) != StrToBinaryOperation.end())
				tokens.push_back(Token{ TokenType::BinaryOperation, curr_s });

			else if (curr == '(')
				tokens.push_back(Token{ TokenType::LeftBracket, curr_s });

			else if (curr == ')')
				tokens.push_back(Token{ TokenType::RightBracket, curr_s });

			else throw std::invalid_argument("Unidentified token: " + curr_s);
		}

		if (numbuf.str().size() > 0)
			tokens.push_back(Token{ TokenType::Number, numbuf.str() });

		else if (charbuf.str().size() > 0)
			_TokeniseChars(charbuf, tokens);

		return tokens;
	}
}
