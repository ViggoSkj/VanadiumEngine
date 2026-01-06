#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;
layout (location = 2) in vec2 symbolPosition;
layout (location = 3) in vec2 position;

#include res/shaders/ubos/renderSurface.shader
#include res/shaders/ubos/camera.shader

uniform vec4 u_rect;
uniform vec2 u_symbolSize;
out vec2 uv;

void main()
{
    vec2 size = u_rect.zw - u_rect.xy;
    vec2 pixelCoordinates = (aPos.xy * size + position * 2.0)/resolution.xy;
    gl_Position = vec4(pixelCoordinates, aPos.z, 1.0);
    gl_Position.x -= 1.0;
    gl_Position.y = 1.0 - gl_Position.y;
    uv = symbolPosition + vec2(aCoord.x, 1.0 - aCoord.y) * u_symbolSize;
}

#shader fragment
#version 400 core
out vec4 FragColor;
in vec2 uv;

uniform sampler2D u_sampler;

void main()
{
    FragColor = texture2D(u_sampler, uv) + vec4(1.0,1.0,1.0,0.3);
}