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
	Lexa::Window::Init(800, 600);


	unsigned int shader = Lexa::Shader::CreateShader("Surface.vs", "Surface.fs");
	auto tokens = Interpreter::Tokenise("sin(x) + cos(y)");
	auto pTree = Interpreter::Parse(tokens);
	auto eval = Interpreter::Eval2D(pTree);
	Lexa::Surface renderer(std::move(eval), -2.0f, 2.0f, -2.0f, 2.0f, 0.1f);
	Lexa::Camera::SetCenterOfRotation(renderer.GetCentroid());
	while (true)
	{  
		Lexa::Window::Clear();
		renderer.Draw(Lexa::Camera::View(), Lexa::Camera::Projection(), Lexa::Camera::Direction());
		Lexa::Window::Refresh();
	}
}