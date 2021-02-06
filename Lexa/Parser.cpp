#include "Parser.h"


namespace Lexa
{
	namespace Interpreter
	{
		void _Pop(std::vector<ParseTree>& pTrees, std::vector<Token>& stack)
		{
			if (stack.size() == 0) throw std::invalid_argument("Could not parse expression");
			
			if (stack.back().type == TokenType::BinaryOperation)
			{
				if (pTrees.size() < 2) throw std::invalid_argument("Could not parse expression");
				ParseTree left(std::move(pTrees[pTrees.size() - 2]));
				ParseTree right(std::move(pTrees[pTrees.size() - 1]));
				pTrees.pop_back();
				pTrees.pop_back();
				pTrees.emplace_back(stack.back(), std::move(left), std::move(right));
			}

			else if (stack.back().type == TokenType::Function)
			{
				if (pTrees.size() < 1) throw std::invalid_argument("Could not parse expression");
				ParseTree left(std::move(pTrees.back()));
				pTrees.pop_back();
				pTrees.emplace_back(stack.back(), std::move(left), true);
			}

			else throw std::invalid_argument("Could not parse expression");

			stack.pop_back();
		}

		
		ParseTree Parse(std::vector<Token> tokens)
		{
			std::vector<ParseTree> partialTrees;
			std::vector<Token> stack;

			tokens.insert(tokens.begin(), Token{ TokenType::LeftBracket, "(" });
			tokens.push_back(Token{ TokenType::RightBracket, ")" });

			for (size_t i = 0; i < tokens.size(); ++i)
			{
				Token t = tokens[i];
				
				switch (t.type)
				{
				case TokenType::Number:
				case TokenType::Variable:
				case TokenType::MathConstant:
					partialTrees.emplace_back(t);
					break;

				case TokenType::Function:
					stack.push_back(t);
					break;

				case TokenType::BinaryOperation:

					while (stack.size() > 0 && 
						   stack.back().type != TokenType::LeftBracket &&
						   OperatorPrecedence.at(StrToBinaryOperation.at(stack.back().value)) >=
						   OperatorPrecedence.at(StrToBinaryOperation.at(t.value)))
					{
						_Pop(partialTrees, stack);
					}

					stack.push_back(t);
					break;

				case TokenType::LeftBracket:
					if (i + 1 == tokens.size()) throw std::invalid_argument("Mismatched parentheses");
					else
					{
						Token next = tokens[i + 1];
						if (next.type == TokenType::BinaryOperation && StrToBinaryOperation.at(next.value) == BinaryOperation::Minus)
							tokens.insert(tokens.begin() + i + 1, Token{ TokenType::Number, "0" });

						stack.push_back(t);
						break;
					}

				case TokenType::RightBracket:
					while (stack.size() > 0 && stack.back().type != TokenType::LeftBracket)
					{
						_Pop(partialTrees, stack);
					}
					if (stack.size() == 0) throw std::invalid_argument("Mismatched parentheses");
					stack.pop_back(); //pop the left bracket
					if (stack.size() > 0 && stack.back().type == TokenType::Function) _Pop(partialTrees, stack); //pop function
					break;

				default:
					throw std::invalid_argument("Unrecognised symbol: " + t.value);
					break;
				}
			}

			if (partialTrees.size() == 0 || stack.size() > 0) throw std::invalid_argument("Could not parse expression");
			return std::move(partialTrees.back());
		}
	}
}