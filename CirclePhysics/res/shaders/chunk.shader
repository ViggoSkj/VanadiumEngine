#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;
layout (location = 2) in float x;
layout (location = 3) in float y;
layout (location = 4) in float type;

#include res/lib/CameraUniformObject.shader

out vec4 color;
out vec2 uv;

const vec4 colors[3] = vec4[3](
    vec4(1.0, 0.0, 0.0, 1.0),
    vec4(0.0, 1.0, 0.0, 1.0),
    vec4(0.0, 0.0, 1.0, 1.0)
);

uniform float u_size;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x + x * u_size, aPos.y + y * u_size, aPos.z, 1.0);
    color = colors[int(type*255)];
    uv = aCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec4 color;
in vec2 uv;


void main()
{
    FragColor = color;
}