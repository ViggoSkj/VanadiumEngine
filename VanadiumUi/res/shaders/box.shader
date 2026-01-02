#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

#include res/shaders/ubos/renderSurface.shader
#include res/shaders/ubos/camera.shader

uniform mat4 u_model;
 
out vec2 uv;

void main()
{
    gl_Position = projection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

#shader fragment
#version 400 core
out vec4 FragColor;
in vec2 uv;

void main()
{
    FragColor = vec4(uv, 1.0, 1.0);
}