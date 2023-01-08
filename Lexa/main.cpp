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
#include "RenderState.h"
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
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    const int FONT_SIZE = 36;

    TextManager t;
    t.AddFont("Niko", "times.ttf", FONT_SIZE);

    const TextureAtlas& p = t.GetFont("Niko", FONT_SIZE);

    auto& rs = RenderState::Instance();

    Textbox tb(400, 100, 0,0, "Niko", FONT_SIZE);

    std::shared_ptr<VertexBuffer> vao = std::make_shared<VertexBuffer>(std::vector<int>{2});

    float xx = 2.f * tb.GetPosition().first / window.GetWidth() - 1.f;
    float yy = 2.f * tb.GetPosition().second / window.GetHeight() - 1.f;
    float XX = xx + 2.f * tb.GetWidth() / window.GetWidth();
    float YY = yy + 2.f * tb.GetHeight() / window.GetHeight();

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

    vao->AddData(vertices);
    vao->AddIndices(indices);

    std::shared_ptr<Shader> s1 = std::make_shared<Shader>("Quad.vs", "Quad.fs");
    std::shared_ptr<Shader> s2 = std::make_shared<Shader>("Default.vs", "Default.fs");
    std::shared_ptr<Shader> s3 = std::make_shared<Shader>("Surface.vs", "Surface.fs");

    InputManager im;

    TextRenderer abc;

    std::shared_ptr<const VertexBuffer> vao2 = abc.GetGeometry();

    SurfaceRenderer s;

    std::shared_ptr<const VertexBuffer> vao3 = s.GetGeometry();

    while (true)
    {
        glm::mat4 casd(1.f);
        rs.SetShader(s2);
        s2->SetUniformMatrix4fv("view", camera.GetView());
        s2->SetUniformMatrix4fv("projection", camera.GetProjection());
        rs.SetVertexBuffer(vao);
        rs.Draw();

        rs.SetShader(s1);
        rs.SetTexture(p.GetTexture());
        rs.SetVertexBuffer(vao2);
        
        abc.Update(tb, t, window);

        rs.Draw();

        window.Update();
        auto cursor = im.GetCursor();
        auto text = im.GetText();
        tb.Update(cursor.m_leftMouseDown, cursor.m_x, cursor.m_y, text, t);
        
        try
        {
            auto eval = Interpreter::Eval2D(Interpreter::Parse(Interpreter::Tokenise(tb.GetText())));
            s.Update(eval, -1.f, 1.f, -1.f, 1.f, 0.1f);
            rs.SetShader(s3);
            s3->SetUniformMatrix4fv("model", glm::mat4(1.f));
            s3->SetUniformMatrix4fv("view", camera.GetView());
            s3->SetUniformMatrix4fv("projection", camera.GetProjection());
            s3->SetUniform3fv("cameraDirection", camera.GetDirection());

            rs.SetVertexBuffer(vao3);
            rs.Draw();
        }
        catch (...)
        {

        }

        camera.Update(window.GetWidth(), window.GetHeight(), im.GetCursor().m_xdelta, im.GetCursor().m_ydelta, im.GetCursor().m_scrolldelta, im.GetCursor().m_leftMouseDown);
        im.Update();
    }
}