#include "MathConstants.h"

#include "Eval.h"


namespace Interpreter
{
	Eval2D::Eval2D(const ParseTree& tree) : expr(MakeEval(tree))
	{
		std::vector<Interpreter::Token> vars = Tree::FindUnique(tree, [](const Interpreter::Token& t) {return t.type == Interpreter::TokenType::Variable; });
		if (vars.size() != 2) throw std::invalid_argument("Expected expression with 2 variables.");
		X = vars[0].value;
		Y = vars[1].value;
	}

	float Eval2D::operator()(float x, float y) const
	{
		float res = Eval(expr, x, y);
		if (isnan(res) || isinf(res)) return NAN;
		return res;
	}

	Eval2D::ExprTree Eval2D::MakeEval(const ParseTree& tree) const
	{
		std::string val = tree.Data().value;
		
		switch (tree.Data().type)
		{
		case Interpreter::TokenType::Number:
			return ExprTree(Node(stof(val)));

		case Interpreter::TokenType::MathConstant:
			return ExprTree(Node(g_StrToMathConstant.at(val)));

		case Interpreter::TokenType::Variable:
			return ExprTree(Node(val));

		case Interpreter::TokenType::Function:
			return ExprTree(Node(g_StrToFunction.at(val)), MakeEval(tree.Left()), true);

		case Interpreter::TokenType::BinaryOperation:
			return ExprTree(Node(g_StrToBinaryOperation.at(val)), MakeEval(tree.Left()), MakeEval(tree.Right()));

		default:
			throw std::invalid_argument("Unexpected token in AST: " + val);
		}
	}

	float Eval2D::Eval(const ExprTree& expr, float x, float y) const
	{
		const Node& n = expr.Data();

		if (std::holds_alternative<BinaryOperation>(n))
		{
			return std::get<BinaryOperation>(n) (Eval(expr.Left(), x, y), Eval(expr.Right(), x, y));
		}

		else if (std::holds_alternative<std::string>(n))
		{
			return (std::get<std::string>(n) == X) ? x : y;
		}

		else if (std::holds_alternative<Function>(n))
		{
			return std::get<Function>(n) (Eval(expr.Left(), x, y));
		}

		else
		{
			return std::get<float>(n);
		}
	}
}
