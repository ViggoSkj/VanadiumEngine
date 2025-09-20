#include "core/Application.h"
#include "core/rendering/rendering.h"
#include "PhysicsApplicationLayer.h"
#include "TestSquareLayer.h"

int main()
{
	Application application;
	application.PushLayer<TestSquareLayer>();
	application.Run();


	return 0;
}