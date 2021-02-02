#pragma once
#include <vector>
#include "Token.h"
#include "Tree.h"


namespace Lexa
{
	namespace Interpreter
	{
		using ParseTree = Tree<Token>;

		const std::unordered_map<Operation, int> OperatorPrecedence
		{
			{Operation::Plus, 0},
			{Operation::Minus, 0},
			{Operation::Times, 1},
			{Operation::Divide, 1},
			{Operation::Raise, 2},
		};

		ParseTree Parse(const std::vector<Token>& tokens);
	}
}