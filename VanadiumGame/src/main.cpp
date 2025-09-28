#include <iostream>
#include "Platformer/PlatformerLayer.h"
#include "Application.h"
#include "Platformer/ComponentStore.h"
#include "Platformer/Entity.h"
#include "Platformer/SpriteRendererLayer.h"
#include "SimdTest/SimdTest.h"

int main()
{
	Application app(1500, 1000);
	app.PushLayer<SpriteRendererLayer>();
	app.Run();

	return 0;
}