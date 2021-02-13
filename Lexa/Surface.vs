#version 330 core
layout (location = 0) 
in vec3 aPos;
out float Intensity;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    Intensity = max(1.0f - dot(aPos, vec3(0.0f, 0.0f, 1.0f)) / length(aPos), 0.0f);
}