#include "Parser.h"


namespace Lexa
{
	namespace Interpreter
	{
		bool _Pop(std::vector<ParseTree>& pTrees, std::vector<Token>& stack)
		{
			if (pTrees.size() < 1 ||
				(stack.back().type == TokenType::BinaryOperation && pTrees.size() < 2))
			{
				return false;
			}

			if (stack.back().type == TokenType::BinaryOperation)
			{
				ParseTree left(std::move(pTrees[pTrees.size() - 2]));
				ParseTree right(std::move(pTrees[pTrees.size() - 1]));
				pTrees.pop_back();
				pTrees.pop_back();
				pTrees.emplace_back(stack.back(), std::move(left), std::move(right));
			}

			else if (stack.back().type == TokenType::Function)
			{
				ParseTree left(std::move(pTrees.back()));
				pTrees.pop_back();
				pTrees.emplace_back(stack.back(), std::move(left), true);
			}

			stack.pop_back();
			return true;
		}


		bool _LookAhead(const std::vector<Token>& tokens, size_t index, bool (*pred)(const Token&))
		{
			if (index + 1 == tokens.size()) return false;
			Token next = tokens[index + 1];
			return pred(next);
		}


		void _CheckImplicitMultiplication(std::vector<Token>& tokens, size_t index)
		{
			if (_LookAhead(tokens, index,
				[](const Token& t) {return t.type == TokenType::Variable || t.type == TokenType::LeftBracket; })
)
			{
				tokens.insert(tokens.begin() + index + 1, Token{ TokenType::BinaryOperation, "*" });
			}
		}


		void _CheckNegativeNumber(std::vector<Token>& tokens, size_t index)
		{
			if (_LookAhead(tokens, index,
				[](const Token& t) {return t.type == TokenType::BinaryOperation && t.value == "-";}))
			{
				tokens.insert(tokens.begin() + index + 1, Token{ TokenType::Number, "0" });
			}
		}

		
		ParseTree Parse(std::vector<Token> tokens)
		{
			std::vector<ParseTree> partialTrees;
			std::vector<Token> stack;

			tokens.insert(tokens.begin(), Token{ TokenType::LeftBracket, "(" });
			tokens.push_back(Token{ TokenType::RightBracket, ")" });

			bool fail = false;
			std::string message = "Could not parse expression";

			for (size_t i = 0; i < tokens.size(); ++i)
			{
				if (fail) break;

				Token t = tokens[i];
				
				switch (t.type)
				{
				case TokenType::Number:
					_CheckImplicitMultiplication(tokens, i);

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
						   OperatorPrecedence.at(stack.back().value) >=
						   OperatorPrecedence.at(t.value))
					{
						if (!_Pop(partialTrees, stack)) 
						{
							fail = true;
							break;
						}
					}

					stack.push_back(t);
					break;

				case TokenType::LeftBracket:
					_CheckNegativeNumber(tokens, i);
					stack.push_back(t);
					break;

				case TokenType::RightBracket:
					_CheckImplicitMultiplication(tokens, i);
					while (stack.size() > 0 && stack.back().type != TokenType::LeftBracket)
					{
						if (!_Pop(partialTrees, stack))
						{
							fail = true;
							break;
						}
					}
					if (stack.size() == 0)
					{
						fail = true;
						message = "Mismatched parentheses";
						break;
					}
					stack.pop_back(); //pop the left bracket
					if (stack.size() > 0 && stack.back().type == TokenType::Function) _Pop(partialTrees, stack); //pop function
					break;

				default:
					fail = true;
					message =  "Unrecognised symbol: " + t.value;
					break;
				}
			}

			if (partialTrees.size() == 0 || stack.size() > 0)
			{
				fail = true;
			}

			if (fail) throw std::invalid_argument(message);
			return std::move(partialTrees.back());
		}
	}
}