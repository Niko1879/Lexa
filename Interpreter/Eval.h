#pragma once
#include <variant>
#include "Tree.h"
#include "Token.h"
#include "Types.h"
#include <string>


namespace Interpreter
{	
	class Eval2D
	{
		using ParseTree = Tree::Tree<Token>;
		using Node = std::variant<Number, Variable, BinaryOperation, Function>;
		using ExprTree = Tree::Tree<Node>;

	public:
		Eval2D(const ParseTree& tree);

		float operator()(float x, float y) const;

	private:
		ExprTree MakeEval(const ParseTree& tree) const;

		float Eval(const ExprTree& expr, float x, float y) const;

		ExprTree expr;

		std::string X;
		std::string Y;
	};
}
