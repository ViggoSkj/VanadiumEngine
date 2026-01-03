#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

uniform mat4 u_model;

out vec2 uv;

#include res/shaders/ubos/renderSurface.shader
#include res/shaders/ubos/camera.shader

void main()
{
    gl_Position = projection * view * u_model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform vec3 m_color;

float sdCircle(vec2 p, float r)
{
    return length(p) - r;
}

void main()
{
    vec2 cord = uv * vec2(1.0, u_length);

    vec2 box = vec2(0.125, u_length * 0.5 - 0.3);

    float d = 0.1;

    vec3 colorFill = m_color;
    vec3 colorEdge = m_color * 2.0;

    colorFill *= (1.0 - uv.y) * 0.3 + 0.7;

    float dist = sdCircle(vec2(0.5,0.5) - uv , 0.5 - d);
    if (dist <= d)
    {
        if (dist <= d/2.0)
            FragColor = vec4(colorFill, 1.0);
        else
            FragColor = vec4(colorEdge, 1.0);
    }
}