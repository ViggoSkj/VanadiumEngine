#include "core/Application.h"
#include "core/rendering/rendering.h"
#include "PhysicsApplicationLayer.h"
#include "TestSquareLayer.h"
#include "core/AssetManager/AssetTypes/Shader/ShaderSourceObject.h"

int main()
{
    Application app;
	app.PushLayer<TestSquareLayer>();
	app.Run();

	return 0;
}