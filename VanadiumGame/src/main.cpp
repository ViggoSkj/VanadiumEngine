#include <iostream>
#include "Platformer/PlatformerLayer.h"
#include "Application.h"
#include "Platformer/ComponentStore.h"
#include "Platformer/Entity.h"

class FloatComponent : public Component
{
public:
	float value;
};

class IntComponent : public Component
{
public:
	int value;
};

void AddNumberComponents(Entity& e, int a, float b)
{
	ComponentRef intRef = e.AddComponent<IntComponent>();
	ComponentRef floatRef = e.AddComponent<FloatComponent>();

	IntComponent& intComponent = e.GetComponent<IntComponent>(intRef);
	FloatComponent& floatComponent = e.GetComponent<FloatComponent>(floatRef);

	intComponent.value = a;
	floatComponent.value = b;
}
void LogNumberComponents(Entity& e)
{
	IntComponent& intComponent = e.GetComponent<IntComponent>();
	FloatComponent& floatComponent = e.GetComponent<FloatComponent>();

	std::cout << intComponent.value<< std::endl;
	std::cout << floatComponent.value << std::endl;
}

int main()
{
	/*
	Application app;
	app.PushLayer<PlatformerLayer>();
	app.Run();
	*/

	for (int i = 0; i < 1000; i++)
	{

		Entity e1;
		AddNumberComponents(e1, 1, 2.5);
		LogNumberComponents(e1);
	}

	return 0;
}