#version 330 core
in float intensity;
out vec4 FragColor;

void main()
{
    FragColor = intensity*vec4(0.5f, 0.5f, 0.5f, 1.0f);
} 