#include <glad/glad.h>
#include <Lexer.h>
#include <Parser.h>
#include <chrono>

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

    bool mouseDown = false;
    InputManager::s_OnMouseButton.Register([&textbox, &window, &textManager, &mouseDown](InputManager::OnMouseButtonParams p)
        {
            auto [x, y] = InputManager::GetCursorPos(window);
            auto [xpos, ypos] = textbox.GetPosition();
            bool isWithinBounds = xpos <= x && x <= xpos + textbox.GetWidth() && ypos <= y && y <= ypos + textbox.GetHeight();
            
            if (p.action == InputManager::Action::PRESS || p.action == InputManager::Action::REPEAT)
            {
                mouseDown = true;
                textbox.SetActive(false);
                if (isWithinBounds)
                {
                    textbox.SetCursorPos(x, y);
                    textbox.BeginHighlightRegion();
                }
            }

            else
            {
                mouseDown = false;
                if (isWithinBounds)
                {
                    textbox.SetActive(true);
                    textbox.EndHighlightRegion();
                }
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
    bool insideTextbox = false;
    InputManager::s_OnMouseMove.Register([&camera, &rotateCamera, &insideTextbox](InputManager::OnMouseMoveParams p)
        {
            if (rotateCamera && !insideTextbox)
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


    auto timer = std::chrono::high_resolution_clock::now();
    bool showCursor = true;
    while (true)
    {
        auto [xpos, ypos] = textbox.GetPosition();
        auto [x, y] = InputManager::GetCursorPos(window);
        insideTextbox = (xpos <= x && x <= xpos + textbox.GetWidth() && ypos <= y && y <= ypos + textbox.GetHeight());
        if (mouseDown && insideTextbox)
            textbox.SetCursorPos(x, y);

        glViewport(0, 0, window.GetWidth(), window.GetHeight());
        window.Clear();

        defaultShader.Bind();
        quadRenderer.Generate(textbox.GetPosition().first, textbox.GetPosition().second, textbox.GetWidth(), textbox.GetHeight(), window);
        const VertexBuffer& vao = quadRenderer.GetGeometry();
        vao.Bind();
        defaultShader.SetUniform4fv("color", glm::vec4(1.f, 1.f, 1.f, 1.f));
        glDrawElements(GL_TRIANGLES, vao.GetSize(), GL_UNSIGNED_INT, 0);

        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - timer).count();
        if (duration >= 700ll)
        {
            showCursor = !showCursor;
            timer = now;
        }

        if (showCursor)
        {
            defaultShader.SetUniform4fv("color", glm::vec4(0.f, 0.f, 0.f, 1.f));
            quadRenderer.Generate(textbox.GetCursorPos(), textbox.GetPosition().second + 1, 1, 0.9 * textbox.GetHeight() - 1, window);
            glDrawElements(GL_TRIANGLES, vao.GetSize(), GL_UNSIGNED_INT, 0);
        }

        if (insideTextbox)
        {
            auto [b, e] = textbox.GetHighlightRegion();
            defaultShader.SetUniform4fv("color", glm::vec4(0.f, 0.f, 1.f, 0.2f));
            quadRenderer.Generate(b, textbox.GetPosition().second, e - b, textbox.GetHeight(), window);
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