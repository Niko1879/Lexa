#pragma once
#include <vector>
#include "Token.h"
#include "Tree.h"


namespace Lexa
{
	namespace Interpreter
	{
		using ParseTree = Tree<Token>;

		ParseTree Parse(const std::vector<Token>& tokens);
	}
}