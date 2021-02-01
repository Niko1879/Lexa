#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace Lexa
{
	namespace Interpreter
	{
		enum class TokenType
		{
			Number,
			Operation,
		};


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


		struct Token
		{
			TokenType type;
			std::string value;
		};


		bool operator==(const Token& t1, const Token& t2);


		std::vector<Token> Tokenise(const std::string& expression);
	}
};

