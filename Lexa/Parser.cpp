#include "Parser.h"


namespace Lexa
{
	namespace Interpreter
	{
		void _Pop(std::vector<ParseTree>& pTrees, std::vector<Token>& stack)
		{
			ParseTree left(std::move(pTrees[pTrees.size() - 2]));
			ParseTree right(std::move(pTrees[pTrees.size() - 1]));
			pTrees.pop_back();
			pTrees.pop_back();
			pTrees.emplace_back(stack.back(), std::move(left), std::move(right));
			stack.pop_back();
		}

		
		ParseTree Parse(const std::vector<Token>& tokens)
		{
			std::vector<ParseTree> partialTrees;
			std::vector<Token> stack;

			for (Token t : tokens)
			{
				switch (t.type)
				{
				case TokenType::Number:
					partialTrees.emplace_back(t);
					break;

				case TokenType::Operation:

					while (stack.size() > 0 && 
						   stack.back().type != TokenType::LeftBracket &&
						   OperatorPrecedence.at(Operations.at(stack.back().value)) >= 
						   OperatorPrecedence.at(Operations.at(t.value)))
					{
						_Pop(partialTrees, stack);
					}

					stack.push_back(t);
					break;

				case TokenType::LeftBracket:
					stack.push_back(t);
					break;

				case TokenType::RightBracket:
					while (stack.size() > 0 && stack.back().type != TokenType::LeftBracket)
					{
						_Pop(partialTrees, stack);
					}
					if (stack.size() > 0) stack.pop_back();
					break;

				default:
					throw std::invalid_argument("Could not parse expression");
					break;
				}
			}

			while (stack.size() > 0)
			{
				_Pop(partialTrees, stack);
			}

			return std::move(partialTrees.back());
		}
	}
}