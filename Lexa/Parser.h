#pragma once
#include <vector>
#include "Token.h"
#include "Tree.h"


namespace Lexa
{
	namespace Interpreter
	{
		using ParseTree = Tree::Tree<Token>;

		ParseTree Parse(std::vector<Token> tokens);
	}
}