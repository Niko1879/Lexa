#pragma once
#include "Token.h"
#include "Tree.h"

namespace InterpreterTest
{
	using Tok = Lexa::Interpreter::Token;
	using Type = Lexa::Interpreter::TokenType;
	using PTree = Lexa::Tree<Tok>;
}