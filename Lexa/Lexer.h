#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include "Token.h"


namespace Interpreter
{
	std::vector<Token> Tokenise(const std::string& expression);
}

