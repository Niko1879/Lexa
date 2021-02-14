#include "Window.h"
#include "Surface.h"
#include "Shader.h"
#include "Lexer.h"
#include "Parser.h"
#include "Eval.h"
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>


int main()
{
	//test
	Lexa::Window window(1920, 1080);
	unsigned int shader = Lexa::Shader::CreateShader("Surface.vs", "Surface.fs");
	auto tokens = Interpreter::Tokenise("x^2 + y^2");
	auto pTree = Interpreter::Parse(tokens);
	auto eval = Interpreter::Eval2D(pTree);
	Lexa::Surface surface(std::move(eval), shader);
	surface.Generate(-0.5f, 0.5f, -0.5f, 0.5f, 0.01f);

	while (true)
	{  
		window.Clear();
		surface.Draw();
		window.Refresh();
	}
}