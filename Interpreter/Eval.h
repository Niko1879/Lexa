#pragma once
#include <string>
#include <variant>

#include "Tree.h"
#include "Token.h"


namespace Interpreter
{	
	class Eval2D
	{
		using ParseTree = Tree::Tree<Interpreter::Token>;

	public:
		Eval2D(const ParseTree& tree);

		float operator()(float x, float y) const;

	private:
		using Node = std::variant<float, std::string, float(*)(float, float), float(*)(float)>;
		using ExprTree = Tree::Tree<Node>;

		ExprTree MakeEval(const ParseTree& tree) const;

		float Eval(const ExprTree& expr, float x, float y) const;

		ExprTree expr;

		std::string X;
		std::string Y;
	};
}
