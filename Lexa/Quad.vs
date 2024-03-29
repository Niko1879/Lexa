#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoord;
out vec2 fTexCoord;

void main()
{
    gl_Position = vec4(vertex, 0.f, 1.f);
    fTexCoord = texCoord;
}