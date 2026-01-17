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
out vec2 size;

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
    size = vec2(width, height);
}

#shader fragment
#version 400 core
out vec4 FragColor;
in vec2 uv;
in vec2 size;

uniform vec4 u_border;
uniform vec4 u_padding;
uniform vec2 u_content;

uniform vec4 u_color; 

uniform float u_rounding;

float sdBox(in vec2 p, in vec2 b)
{
    vec2 d = abs(p) - b;
    return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
}

float sdRoundedBox( in vec2 p, in vec2 b, in vec4 r )
{
    r.xy = (p.x>0.0)?r.xy : r.zw;
    r.x  = (p.y>0.0)?r.x  : r.y;
    vec2 q = abs(p)-b+r.x;
    return min(max(q.x,q.y),0.0) + length(max(q,0.0)) - r.x;
}

void main()
{
    vec2 halfSize = size * 0.5;
    vec2 pixel = size * uv;
    vec2 centerizedPixel = halfSize - pixel;

    vec4 color = u_color;

    float borderOuterDist = sdRoundedBox(centerizedPixel, halfSize, vec4(u_rounding,u_rounding,u_rounding,u_rounding));

    if (borderOuterDist > 0)
    {
        color = vec4(0.0,0.0,0.0,0.0);
    } else if (borderOuterDist > -u_border.x)
    {
        color *= 0.8;
    }

    // some sort of anti aliasing
    color.a *= min(1, -borderOuterDist);

    FragColor = color;
}