PRAGMA VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

out vec2 uv;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

PRAGMA FRAGMENT
#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform sampler2D u_sampler;

void main()
{
    FragColor = texture2D(u_sampler, uv);
}