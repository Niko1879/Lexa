#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
out float intensity;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraDirection;

void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0f);
    //intensity = max(0.0f, dot(-cameraDirection, normal));
    intensity = max(dot(cameraDirection, normal), dot(-cameraDirection, normal));
}