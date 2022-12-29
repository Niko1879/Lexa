#version 330 core
in vec2 fTexCoord;
out vec4 color;

uniform sampler2D uSampler;

void main()
{    
    color = texture(uSampler, fTexCoord);
} 