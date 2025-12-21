#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;

out vec2 uv;

#include res/lib/CameraUniformObject.shader

void main()
{
    gl_Position = projection * view  * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 uv;

float distSquared( vec2 A, vec2 B )
{

    vec2 C = A - B;
    return dot( C, C );

}

void main()
{
    FragColor = vec4(uv, 1.0, 1.0);
}