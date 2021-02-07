#pragma once
#include <variant>
#include "Tree.h"
#include "Token.h"
#include <string>


namespace Lexa
{
	namespace Interpreter
	{	
		class Eval2D
		{
			using Operator = float (*)(float, float);
			using Function = float (*)(float);
			using Number = float;
			using Variable = std::string;
			using Node = std::variant<Number, Variable, Operator, Function>;
			using ExprTree = Tree<Node>;

		public:
			Eval2D(Tree<Token>&& tree);

			float operator()(float x, float y);

		private:
			ExprTree expr;

			ExprTree MakeEval(Tree<Token>&& tree);

			float Eval(float x, float y);
		};
	}
}
