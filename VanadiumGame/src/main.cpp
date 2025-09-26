#include <iostream>
#include "TestSquareLayer.h"
#include "Application.h"

int main()
{
    Application app;
	app.PushLayer<TestSquareLayer>();
	app.Run();

	return 0;
}