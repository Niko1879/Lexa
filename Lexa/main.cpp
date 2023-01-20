#include <glad/glad.h>
#include <Lexer.h>
#include <Parser.h>

#include "Window.h"
#include "Camera.h"
#include "InputManager.h"
#include "Shader.h"
#include "TextManager.h"
#include "TextureAtlas.h"
#include "Textbox.h"
#include "VertexBuffer.h"
#include "TextRenderer.h"
#include "SurfaceRenderer.h"
#include "QuadRenderer.h"


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
    const float FONT_SCALE = 0.7f;
    const std::string FONT = "times";

    Shader quadShader("Quad.vs", "Quad.fs");

    TextManager textManager;
    textManager.AddFont(FONT, "times.ttf", FONT_SIZE, quadShader);
    const TextureAtlas& fontTex = textManager.GetFont(FONT, FONT_SIZE).textureAtlas;

    Textbox textbox(640, 30, window.GetWidth() / 2.f - 320.f, window.GetHeight() - 50.f, FONT, FONT_SIZE, FONT_SCALE);

    Shader defaultShader("Default.vs", "Default.fs");
    Shader surfaceShader("Surface.vs", "Surface.fs");

    TextRenderer textRenderer;
    SurfaceRenderer surfaceRenderer;
    QuadRenderer quadRenderer;

    InputManager::s_OnCharacterInput.Register([&textbox, &textManager](InputManager::OnCharacterInputParams p) 
        {
            textbox.AddText(p.c, textManager);
        });

    InputManager::s_OnMouseButton.Register([&textbox, &window, &textManager](InputManager::OnMouseButtonParams p)
        {
            bool b1 = p.action == InputManager::Action::PRESS && p.button == InputManager::MouseButton::LEFT;
            auto[x, y] = InputManager::GetCursorPos(window);
            auto [xpos, ypos] = textbox.GetPosition();
            bool b2 = xpos <= x && x <= xpos + textbox.GetWidth() &&
                      ypos <= y && y <= ypos + textbox.GetHeight();
            
            if (b1 && b2)
            {
                textbox.SetActive(true);
                textbox.SetCursorPos(x, y, textManager);
            }

            if (!b2)
            {
                textbox.SetActive(false);
            }

            if (b1)
            {
                textbox.SetCursorPos(x, y, textManager);
            }
            
        });

    std::unique_ptr<Interpreter::Eval2D> eval = nullptr;
    InputManager::s_OnKeyInput.Register([&textbox, &textManager, &eval, &surfaceRenderer, &camera](InputManager::OnKeyInputParams p)
        {
            if (p.key == InputManager::Key::BACKSPACE && (p.action == InputManager::Action::PRESS || p.action == InputManager::Action::REPEAT))
            {
                textbox.AddText("\b", textManager);
            }
        
            if (p.key == InputManager::Key::ENTER && (p.action == InputManager::Action::PRESS || p.action == InputManager::Action::REPEAT))
            {
                try
                {
                    eval.reset(new Interpreter::Eval2D(Interpreter::Parse(Interpreter::Tokenise(textbox.GetText()))));
                    surfaceRenderer.Generate(*eval, -1.f, 1.f, -1.f, 1.f, 0.1f);
                    camera.SetCenterOfRotation(surfaceRenderer.GetCentroid());
                }
                catch (...)
                {
                    eval = nullptr;
                }
            }
        });

    bool rotateCamera = false;
    InputManager::s_OnMouseMove.Register([&camera, &rotateCamera](InputManager::OnMouseMoveParams p)
        {
            if (rotateCamera)
            {
                camera.Rotate(p.xDelta, p.yDelta);
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

    InputManager::s_OnWindowResize.Register([&window, &textbox](InputManager::OnWindowResizeParams p)
        {
            glViewport(0, 0, p.width, p.height);
            window.SetDimensions(p.width, p.height);
            textbox.SetPosition(window.GetWidth() / 2.f - 320.f, window.GetHeight() - 50.f);
        });


    int timer = 0;
    bool showCursor = true;
    while (true)
    {
        glViewport(0, 0, window.GetWidth(), window.GetHeight());
        window.Clear();

        defaultShader.Bind();
        quadRenderer.Generate(textbox.GetPosition().first, textbox.GetPosition().second, textbox.GetWidth(), textbox.GetHeight(), window);
        const VertexBuffer& vao = quadRenderer.GetGeometry();
        vao.Bind();
        defaultShader.SetUniform3fv("color", glm::vec3(1.f, 1.f, 1.f));
        glDrawElements(GL_TRIANGLES, vao.GetSize(), GL_UNSIGNED_INT, 0);

        ++timer;
        if (timer % 100 == 0)
        {
            timer = 0;
            showCursor = !showCursor;
        }

        if (showCursor)
        {
            defaultShader.SetUniform3fv("color", glm::vec3(0.f, 0.f, 0.f));
            quadRenderer.Generate(textbox.GetCursorPos(), textbox.GetPosition().second + 1, 1, 0.9 * textbox.GetHeight() - 1, window);
            glDrawElements(GL_TRIANGLES, vao.GetSize(), GL_UNSIGNED_INT, 0);
        }

        quadShader.Bind();
        fontTex.GetTexture().Bind();
        textRenderer.Generate(textbox, textManager, window);
        glDrawElements(GL_TRIANGLES, textRenderer.GetGeometry().GetSize(), GL_UNSIGNED_INT, 0);

        if (eval)
        {
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
            surfaceRenderer.GetGeometry().Bind();
            surfaceShader.Bind();
            glm::mat4 m(1.f);
            surfaceShader.SetUniformMatrix4fv("model", m);
            surfaceShader.SetUniformMatrix4fv("view", camera.GetView());
            surfaceShader.SetUniformMatrix4fv("projection", camera.GetProjection());
            surfaceShader.SetUniform3fv("cameraDirection", camera.GetDirection());
            glViewport(0, 0, window.GetWidth(), window.GetHeight() - textbox.GetHeight() - (window.GetHeight() - textbox.GetPosition().second));
            glDrawElements(GL_TRIANGLES, surfaceRenderer.GetGeometry().GetSize(), GL_UNSIGNED_INT, 0);
        }
        
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glfwSwapBuffers(window.Get());
        glfwPollEvents();
    }
}