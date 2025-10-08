#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

out vec2 uv;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

void main()
{
    gl_Position = projection * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 uv;

void main()
{
    vec2 size = vec2(10.0, 10.0);

    vec3 color = vec3(0.1, 0.2, 8.0);

    ivec2 pos = ivec2(uv*size);

    FragColor=vec4(uv, 1.0, 1.0);

    if (pos.x%2 ==  pos.y%2)
    {
        FragColor *= 0.9;
    }
}