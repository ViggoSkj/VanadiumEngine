#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

#include res/shaders/ubos/renderSurface.shader
#include res/shaders/ubos/camera.shader

uniform vec2 u_position;

uniform vec4 u_border;
uniform vec4 u_padding;
uniform vec2 u_content;

out vec2 uv;

void main()
{
    float width = u_border.y + u_border.w +
                  u_padding.y + u_padding.w +
                  u_content.x;
    
    float height = u_border.x + u_border.z +
                  u_padding.x + u_padding.z +
                  u_content.y;

    vec2 pixelCoordinates = (u_position * 2 + aPos.xy * vec2(width, height))/resolution.xy;
    gl_Position = vec4(pixelCoordinates, aPos.z, 1.0);
    gl_Position.x -= 1.0;
    gl_Position.y = 1.0 - gl_Position.y;
    uv = aCoord;
}

#shader fragment
#version 400 core
out vec4 FragColor;
in vec2 uv;

uniform vec4 u_color; 

void main()
{
    FragColor = u_color;
}