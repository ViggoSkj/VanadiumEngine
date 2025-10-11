#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

out vec2 uv;

#include res/lib/CameraUniformObject.shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    uv = (inverse(projection * view) * vec4(aPos, 1.0)).xy;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 uv;

void main()
{
    vec2 size = vec2(10.0, 10.0);

    vec3 color = vec3(0.1, 0.2, 8.0);

    ivec2 pos = ivec2(round(uv*size));

    FragColor=vec4(0.2, 0.4, 0.7, 1.0);

    if ((pos.x + pos.y)%2 == 0)
    {
        FragColor *= 0.9;
    }
}