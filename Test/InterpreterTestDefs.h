#pragma once
#include "Token.h"
#include "Tree.h"

#define TOKENS std::vector<Interpreter::Token>
#define NUM(x) Interpreter::Token{Interpreter::TokenType::Number, x}
#define VAR(x) Interpreter::Token{Interpreter::TokenType::Variable, x}
#define MCON(x) Interpreter::Token{Interpreter::TokenType::MathConstant, x}
#define FUN(x) Interpreter::Token{Interpreter::TokenType::Function, x}
#define OP(x) Interpreter::Token{Interpreter::TokenType::BinaryOperation, x}
#define LBRACKET Interpreter::Token{Interpreter::TokenType::LeftBracket, "("}
#define RBRACKET Interpreter::Token{Interpreter::TokenType::RightBracket, ")"}
#define LEAF(name, x) Tree::Tree<Interpreter::Token> name(std::move(x))
#define BRANCH(name, a, b, c) Tree::Tree<Interpreter::Token> name(std::move(a), std::move(b), std::move(c))
#define EVAL(name, root) Interpreter::Eval2D name(std::move(root))
#define FLOAT_EQ(a, b) (abs(a - b) < 0.001f)

namespace InterpreterTest
{
	using Tok = Interpreter::Token;
	using Type = Interpreter::TokenType;
	using PTree = Tree::Tree<Tok>;
}