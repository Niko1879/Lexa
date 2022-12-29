#pragma once
#include <vector>
#include <string>
#include "Token.h"


namespace Interpreter
{
	std::vector<Token> Tokenise(const std::string& expression);
}

