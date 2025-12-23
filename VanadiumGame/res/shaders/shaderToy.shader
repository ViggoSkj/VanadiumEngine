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
uniform float u_thickness;

float sdSegment(in vec2 p, in vec2 a, in vec2 b)
{
    vec2 pa = p - a;
    vec2 ba = b - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    return length(pa - ba * h);
}

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

float sdOrientedBox(in vec2 p, in vec2 a, in vec2 b, float th)
{
    float l = length(b - a);
    vec2 d = (b - a) / l;
    vec2 q = (p - (a + b) * 0.5);
    q = mat2(d.x, - d.y, d.y, d.x) * q;
    q = abs(q) - vec2(l, th) * 0.5;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0);
}

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

float sdCircle(vec2 p, float r)
{
    return length(p) - r;
}

float distSquared(vec2 A, vec2 B)
{
    vec2 C = A - B;
    return dot(C, C);
}

void main()
{
    vec2 cord = uv * vec2(1.0, u_length);

    vec2 box = vec2(0.5 * (u_thickness - 0.01 * 2), u_length * 0.5 - 0.05);

    vec3 colorFill = vec3(0.44313725490196076, 0.19607843137254902, 0.792156862745098);
    vec3 colorEdge = colorFill * 2.0;

    colorFill *= (1.0 - uv.y) * 0.3 + 0.7;

    float tri = sdEquilateralTriangle(vec2(0.5, 0.1) - cord, u_thickness);
    float c = 0.03;
    float line = sdBox(vec2(0.5, u_length / 2.0 + 0.03) - cord, box);
    float dist = min(tri, line);
    float s = smoothstep(0.011, 0.01, dist);
    FragColor = vec4(0.0,0.0,0.0,0.0);

    if (dist <= 0.01)
    {
        FragColor = vec4(colorFill, 1.0);
    }
}