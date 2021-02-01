#pragma once
#include <vector>
#include "Token.h"
#include "Tree.h"


namespace Lexa
{
	namespace Interpreter
	{
		Tree<Token> Parse(const std::vector<Token>& tokens);
	}
}