#version 330 core
in float Intensity;
out vec4 FragColor;

void main()
{
    FragColor = vec4(Intensity*vec3(0.5f, 0.5f, 0.5f), 1.0f);
} 