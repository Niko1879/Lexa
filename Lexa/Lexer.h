#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include "Token.h"


namespace Lexa
{
	namespace Interpreter
	{
		enum class Operation
		{
			Plus,
			Minus,
			Times,
			Divide,
			Raise,
		};


		const std::unordered_map<std::string, Operation> Operations
			{
				{"+", Operation::Plus},
				{"-", Operation::Minus},
				{"*", Operation::Times},
				{"/", Operation::Divide},
				{"^", Operation::Raise},
			};


		std::vector<Token> Tokenise(const std::string& expression);
	}
};

