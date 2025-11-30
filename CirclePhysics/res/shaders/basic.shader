PRAGMA VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCoord;
layout (location = 2) in vec4 aMat1;
layout (location = 3) in vec4 aMat2;
layout (location = 4) in vec4 aMat3;
layout (location = 5) in vec4 aMat4;

out vec2 uv;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * mat4(aMat1, aMat2, aMat3, aMat4) * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = aCoord;
}

PRAGMA FRAGMENT
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
    if (distSquared(uv, vec2(0.5, 0.5)) > 0.25)
        FragColor = vec4(0.0,0.0,0.0,0.0);
    else 
        FragColor = vec4(vec3(uv,0.0) * dot(uv - vec2(0.0, 0.5), normalize(vec2(1.0, 1.0))), 1.0);
}