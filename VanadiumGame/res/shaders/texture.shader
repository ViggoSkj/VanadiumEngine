#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

out vec2 uv;

void main()
{
    gl_Position = projection * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform sampler2D u_sampler;

void main()
{
    FragColor = texture2D(u_sampler, uv);
}