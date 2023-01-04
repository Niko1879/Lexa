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

using namespace Lexa;

int main()
{

    glfwInit();
    Window window(1024, 512);
    window.MakeCurrent();
    Camera camera;
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_DEPTH_TEST);

    TextManager t;
    t.AddFont("Niko", "times.ttf", 48);

    const TextureAtlas& p = t.GetFont("Niko", 48);

    auto& rs = RenderState::Instance();

    Textbox tb(400, 100, 0, 0);

    std::shared_ptr<VertexBuffer> vao = std::make_shared<VertexBuffer>(std::vector<int>{2});


    std::vector<float> vertices
    {
        -1.f, -1.f,                 //bottomleft
        -1.f, -1.f + 2.f * (float)tb.GetHeight() / 512.f,                                  //topleft
        -1.f + 2.f * (float)tb.GetWidth() / 1024.f, -1.f + 2.f * (float)tb.GetHeight() / 512.f,                  //topright,
        -1.f + 2.f * (float)tb.GetWidth() / 1024.f, -1.f  //bottomright
    };

    std::vector<unsigned> indices
    {
        2, 1, 0,
        0, 3, 2
    };

    vao->AddData(vertices);
    vao->AddIndices(indices);

    std::shared_ptr<VertexBuffer> vao2 = std::make_shared<VertexBuffer>(std::vector<int>{2, 2});

    std::shared_ptr<Shader> s1 = std::make_shared<Shader>("Quad.vs", "Quad.fs");
    std::shared_ptr<Shader> s2 = std::make_shared<Shader>("Default.vs", "Default.fs");

    InputManager im;


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
        
        auto text = tb.GetText();
        std::vector<float> d;
        std::vector<unsigned> i;
        float xpos = -1.f;
        float ypos = -0.98f;
        float xinc = 0.0439;
        float yinc = 0.0878;
        int k = 0;
        for (char c : text)
        {
            auto tc = p.GetTexCoords(std::string(1, c));

            auto xd = t.GetCharInfo("Niko", 48, c);
            float dix = xd.yOffset / (float)window.GetHeight();

            float oldy = ypos;
            ypos = ypos - dix;

            //bottomleft
            d.push_back(xpos);
            d.push_back(ypos);
            d.push_back(tc.bottomLeftU);
            d.push_back(tc.bottomLeftV);

            //topleft
            d.push_back(xpos);
            d.push_back(ypos + tc.height);
            d.push_back(tc.topLeftU);
            d.push_back(tc.topLeftV);

            //topright
            d.push_back(xpos + tc.width);
            d.push_back(ypos + tc.height);
            d.push_back(tc.topRightU);
            d.push_back(tc.topRightV);

            //bottomright
            d.push_back(xpos + tc.width);
            d.push_back(ypos);
            d.push_back(tc.bottomRightU);
            d.push_back(tc.bottomRightV);

            i.push_back(2 + k);
            i.push_back(1 + k);
            i.push_back(0 + k);

            i.push_back(0 + k);
            i.push_back(3 + k);
            i.push_back(2 + k);

            k += 4;
            xpos += (float)xd.xOffset / (float)window.GetWidth();
            ypos = oldy;
        }

        vao2->AddData(d);
        vao2->AddIndices(i);

        rs.Draw();

        window.Update();
        auto m_cursor = im.GetCursor();
        auto m_text = im.GetText();
        tb.Update(m_cursor.m_leftMouseDown, m_cursor.m_x, m_cursor.m_y, m_text);
        im.Update();
        
    }
}