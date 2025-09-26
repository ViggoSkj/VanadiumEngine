#include <iostream>
#include "Platformer/PlatformerLayer.h"
#include "Application.h"

int main()
{
    Application app;
	app.PushLayer<PlatformerLayer>();
	app.Run();

	return 0;
}