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
#version 400 core
out vec4 FragColor;
in vec2 uv;

uniform float u_time;
uniform sampler2D u_sampler;

void main()
{
    float timePerFrame = 0.1;
    int frames = 8;

    int frame = int(floor(u_time/timePerFrame));
    frame = int(mod(frame, 8));
    float x = float(frame)/float(frames);
    FragColor = texture2D(u_sampler, vec2(x + uv.x/float(frames), uv.y));
}