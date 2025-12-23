#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

#include res/lib/CameraUniformObject.shader

uniform mat4 u_model;
 
void main()
{
    gl_Position = projection * view * u_model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

#shader fragment
#version 400 core
out vec4 FragColor;

uniform vec4 u_color;

void main()
{
    FragColor = u_color;
}