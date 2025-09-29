#include <iostream>
#include "Platformer/PlatformerLayer.h"
#include "Application.h"
#include "Platformer/SpriteRendererLayer.h"
#include "Platformer/Components/Camera.h"
#include "SimdTest/SimdTest.h"

int main()
{
	Application app(1500, 1000);
	app.PushLayer<SpriteRendererLayer>();
	app.PushLayer<LiveComponentLayer<MovableCameraComponent>>();
	app.Run();

	return 0;
}