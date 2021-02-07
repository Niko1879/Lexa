#pragma once
#include "Token.h"
#include "Tree.h"

#define TOKENS std::vector<Lexa::Interpreter::Token>
#define NUM(x) Lexa::Interpreter::Token{Lexa::Interpreter::TokenType::Number, x}
#define VAR(x) Lexa::Interpreter::Token{Lexa::Interpreter::TokenType::Variable, x}
#define MCON(x) Lexa::Interpreter::Token{Lexa::Interpreter::TokenType::MathConstant, x}
#define FUN(x) Lexa::Interpreter::Token{Lexa::Interpreter::TokenType::Function, x}
#define OP(x) Lexa::Interpreter::Token{Lexa::Interpreter::TokenType::BinaryOperation, x}
#define LBRACKET Lexa::Interpreter::Token{Lexa::Interpreter::TokenType::LeftBracket, "("}
#define RBRACKET Lexa::Interpreter::Token{Lexa::Interpreter::TokenType::RightBracket, ")"}
#define LEAF(name, x) Lexa::Tree<Lexa::Interpreter::Token> name(std::move(x))
#define BRANCH(name, a, b, c) Lexa::Tree<Lexa::Interpreter::Token> name(std::move(a), std::move(b), std::move(c))
#define EVAL(name, root) Lexa::Interpreter::Eval2D name(std::move(root))
#define FLOAT_EQ(a, b) abs(a - b) < 0.000001

namespace InterpreterTest
{
	using Tok = Lexa::Interpreter::Token;
	using Type = Lexa::Interpreter::TokenType;
	using PTree = Lexa::Tree<Tok>;
}