#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"
#include "Window.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "TextureAtlas.h"
#include "TextManager.h"
#include "Textbox.h"
#include "Camera.h"
#include "InputManager.h"
#include "TextRenderer.h"
#include "SurfaceRenderer.h"
#include <Parser.h>
#include <Lexer.h>

using namespace Lexa;

int main()
{

    glfwInit();
    Window window(1024, 512);
    window.MakeCurrent();
    Camera camera;
    camera.Zoom(-3.f);
    camera.SetProjection(1024, 512);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    InputManager::SetContext(window);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int FONT_SIZE = 36;
    const std::string FONT = "times";

    Shader quadShader("Quad.vs", "Quad.fs");

    TextManager textManager;
    textManager.AddFont(FONT, "times.ttf", FONT_SIZE, quadShader);
    const TextureAtlas& fontTex = textManager.GetFont(FONT, FONT_SIZE);

    Textbox textbox(400, 100, 0,0, FONT, FONT_SIZE);

    VertexBuffer vao(std::vector<int>{2});

    float xx = 2.f * textbox.GetPosition().first / window.GetWidth() - 1.f;
    float yy = 2.f * textbox.GetPosition().second / window.GetHeight() - 1.f;
    float XX = xx + 2.f * textbox.GetWidth() / window.GetWidth();
    float YY = yy + 2.f * textbox.GetHeight() / window.GetHeight();

    std::vector<float> vertices
    {
        xx, yy,              //bottomleft
        xx, YY,                                  //topleft
        XX, YY,                  //topright,
        XX, yy  //bottomright
    };

    std::vector<unsigned> indices
    {
        2, 1, 0,
        0, 3, 2
    };

    vao.SetVertexData(vertices);
    vao.SetIndexData(indices);

    Shader defaultShader("Default.vs", "Default.fs");
    Shader surfaceShader("Surface.vs", "Surface.fs");

    TextRenderer textRenderer;
    SurfaceRenderer surfaceRenderer;


    InputManager::s_OnCharacterInput.Register([&textbox, &textManager](InputManager::OnCharacterInputParams p) 
        {
            textbox.AddText(p.c, textManager);
        });

    InputManager::s_OnMouseButton.Register([&textbox, &window](InputManager::OnMouseButtonParams p)
        {
            bool b1 = p.action == InputManager::Action::PRESS && p.button == InputManager::MouseButton::LEFT;
            auto[x, y] = InputManager::GetCursorPos(window);
            auto [xpos, ypos] = textbox.GetPosition();
            bool b2 = xpos <= x && x <= xpos + textbox.GetWidth() &&
                      ypos <= y && y <= ypos + textbox.GetHeight();
            
            if (b1 && b2)
            {
                textbox.SetActive(true);
                textbox.SetCursorPos(x, y);
            }
            
        });

    InputManager::s_OnKeyInput.Register([&textbox, &textManager](InputManager::OnKeyInputParams p)
        {
            if (p.key == InputManager::Key::BACKSPACE && (p.action == InputManager::Action::PRESS || p.action == InputManager::Action::REPEAT))
            {
                textbox.AddText("\b", textManager);
            }
        });

    bool rotateCamera = false;
    bool drawSurface = false;
    InputManager::s_OnMouseMove.Register([&camera, &rotateCamera, &drawSurface](InputManager::OnMouseMoveParams p)
        {
            if (rotateCamera && drawSurface)
            {
                camera.Rotate(p.xDelta, -p.yDelta);
            }
        });

    InputManager::s_OnMouseButton.Register([&rotateCamera](InputManager::OnMouseButtonParams p)
        {
            rotateCamera = (p.action == InputManager::Action::PRESS || p.action == InputManager::Action::REPEAT) && p.button == InputManager::MouseButton::LEFT;
        });

    InputManager::s_OnScroll.Register([&camera](InputManager::OnScrollParams p)
        {
            camera.Zoom(p.amount);
        });


    while (true)
    {
        window.Clear();

        defaultShader.Bind();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, vao.GetSize(), GL_UNSIGNED_INT, 0);

        quadShader.Bind();
        fontTex.GetTexture().Bind();
        textRenderer.Generate(textbox, textManager, window);
        glDrawElements(GL_TRIANGLES, textRenderer.GetGeometry().GetSize(), GL_UNSIGNED_INT, 0);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        std::string eq = textbox.GetText();
        surfaceShader.Bind();
        try
        {
            glm::mat4 m(1.f);
            surfaceShader.SetUniformMatrix4fv("model", m);
            surfaceShader.SetUniformMatrix4fv("view", camera.GetView());
            surfaceShader.SetUniformMatrix4fv("projection", camera.GetProjection());
            surfaceShader.SetUniform3fv("cameraDirection", camera.GetDirection());
            Interpreter::Eval2D eval(Interpreter::Parse(Interpreter::Tokenise(eq)));
            SurfaceRenderer surfaceRenderer;
            surfaceRenderer.Generate(eval, -1.f, 1.f, -1.f, 1.f, 0.1f);
            //camera.SetCenterOfRotation(surfaceRenderer.GetCentroid());
            glDrawElements(GL_TRIANGLES, surfaceRenderer.GetGeometry().GetSize(), GL_UNSIGNED_INT, 0);
            drawSurface = true;
        }
        catch (...)
        {

        }
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glfwSwapBuffers(window.Get());
        glfwPollEvents();
    }
}