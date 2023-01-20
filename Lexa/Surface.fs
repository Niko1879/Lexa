#version 330 core
in vec3 oNormal;
out vec4 FragColor;

uniform vec3 cameraDirection;

void main()
{ 
    vec3 norm = normalize(oNormal);
    float diff = max(abs(dot(norm, cameraDirection)), 0.f);
    vec3 diffuse = diff * vec3(1.f, 1.f, 1.f);
    vec3 ambient = vec3(0.3f, 0.3f, 0.3f);
    FragColor = vec4((diffuse + ambient), 1.f);
} 