#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

uniform mat4 u_model;

out vec2 uv;

#include res/lib/CameraUniformObject.shader

void main()
{
    gl_Position = projection * view * u_model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform float u_length;

float sdEquilateralTriangle(in vec2 p, in float r)
{
    const float k = sqrt(3.0);
    p.x = abs(p.x) - r;
    p.y = p.y + r / k;
    if(p.x + k * p.y > 0.0)
    {
        p = vec2(p.x - k * p.y, - k * p.x - p.y) / 2.0;
    }
    p.x -= clamp(p.x, - 2.0 * r, 0.0);
    return - length(p) * sign(p.y);
}

float sdBox(in vec2 p, in vec2 b)
{
    vec2 d = abs(p) - b;
    return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);
}

void main()
{
    vec2 cord = uv * vec2(1.0, u_length);

    vec2 box = vec2(0.125, u_length * 0.5 - 0.3);

    float d = 0.1;

    vec3 colorFill = vec3(0.44313725490196076, 0.19607843137254902, 0.792156862745098);
    vec3 colorEdge = colorFill * 2.0;

    colorFill *= (1.0 - uv.y) * 0.3 + 0.7;

    float tri = sdEquilateralTriangle(vec2(0.5, 0.6) - cord, 0.5 - d);
    float c = 0.03;
    float line = sdBox(vec2(0.5, u_length/2.0 + 0.1) - cord, box);
    float dist = min(tri, line);
    float s = smoothstep(0.011, 0.01, dist);
    if (dist <= d)
    {
        if (dist <= d/2.0)
            FragColor = vec4(colorFill, 1.0);
        else
            FragColor = vec4(colorEdge, 1.0);
    }
}