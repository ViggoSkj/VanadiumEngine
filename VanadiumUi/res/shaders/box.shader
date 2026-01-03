#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

#include res/shaders/ubos/renderSurface.shader
#include res/shaders/ubos/camera.shader

uniform vec4 u_rect;
 
out vec2 uv;

void main()
{
    vec2 pixelCoordinates = (u_rect.xy * 2 + aPos.xy * (u_rect.zw - u_rect.xy))/resolution.xy;
    gl_Position = vec4(pixelCoordinates, aPos.z, 1.0);
    gl_Position.x -= 1.0;
    gl_Position.y = 1.0 - gl_Position.y;
    uv = aCoord;
}

#shader fragment
#version 400 core
out vec4 FragColor;
in vec2 uv;

void main()
{
    FragColor = vec4(uv, 0.0, 1.0);
}