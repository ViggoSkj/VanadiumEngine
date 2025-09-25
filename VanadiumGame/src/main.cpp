#include <iostream>
#include "core/Application.h"
#include "core/Rendering/rendering.h"
#include "core/Shaders.h"
#include "TestSquareLayer.h"

int main()
{
    Application app;
	app.PushLayer<TestSquareLayer>();
	app.Run();

	return 0;
}