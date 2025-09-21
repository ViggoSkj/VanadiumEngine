#include "core/Application.h"
#include "core/rendering/rendering.h"
#include "PhysicsApplicationLayer.h"
#include "TestSquareLayer.h"

#include "core/AssetManager/AssetTypes/ShaderSourceObject.h"

int main()
{

	const char* source = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec2 aCoord;
        layout(std140) uniform Matrices
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
    )";

	TokenizeShaderSource(source);

	return 0;
}