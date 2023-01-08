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

    std::shared_ptr<Shader> s1 = std::make_shared<Shader>("Quad.vs", "Quad.fs");

    TextManager t;
    t.AddFont("Niko", "times.ttf", FONT_SIZE, *s1);

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

    vao->SetVertexData(vertices);
    vao->SetIndexData(indices);

    std::shared_ptr<Shader> s2 = std::make_shared<Shader>("Default.vs", "Default.fs");
    std::shared_ptr<Shader> s3 = std::make_shared<Shader>("Surface.vs", "Surface.fs");

    InputManager im;

    TextRenderer abc;

    const VertexBuffer& vao2 = abc.GetGeometry();

    SurfaceRenderer s;

    const VertexBuffer& vao3 = s.GetGeometry();

    while (true)
    {
        glm::mat4 casd(1.f);
        s2->Bind();
        s2->SetUniformMatrix4fv("view", camera.GetView());
        s2->SetUniformMatrix4fv("projection", camera.GetProjection());
        vao->Bind();
        rs.Draw(vao->GetSize());

        s1->Bind();
        p.GetTexture().Bind();
        vao2.Bind();
        
        abc.Generate(tb, t, window);

        rs.Draw(vao2.GetSize());

        auto cursor = im.GetCursor();
        auto text = im.GetText();
        tb.SetActive(cursor.leftMouseDown);
        tb.SetCursorPos(cursor.x, cursor.y);
        tb.AddText(text, t);
        
        try
        {
            auto eval = Interpreter::Eval2D(Interpreter::Parse(Interpreter::Tokenise(tb.GetText())));
            s.Generate(eval, -1.f, 1.f, -1.f, 1.f, 0.1f);
            s3->Bind();
            s3->SetUniformMatrix4fv("model", glm::mat4(1.f));
            s3->SetUniformMatrix4fv("view", camera.GetView());
            s3->SetUniformMatrix4fv("projection", camera.GetProjection());
            s3->SetUniform3fv("cameraDirection", camera.GetDirection());

            vao3.Bind();
            rs.Draw(vao3.GetSize());
        }
        catch (...)
        {

        }

        camera.SetProjection(window.GetWidth(), window.GetHeight());
        camera.Zoom(im.GetCursor().scrolldelta);
        if (im.GetCursor().leftMouseDown)
            camera.Rotate(im.GetCursor().xdelta, im.GetCursor().ydelta);
        im.Update();
    }
}