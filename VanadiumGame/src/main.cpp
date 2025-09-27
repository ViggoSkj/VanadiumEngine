#include <iostream>
#include "Platformer/PlatformerLayer.h"
#include "Application.h"
#include "Platformer/ComponentStore.h"


class IntComponent : public Component
{
public:
	int Value;
};

int main()
{
	/*
	Application app;
	app.PushLayer<PlatformerLayer>();
	app.Run();
	*/

	ComponentStore<IntComponent> store;

	const int count = 1000000;
	std::vector<ComponentRef<IntComponent>> refs;

	for (int i = 0; i < count; i++)
	{
		if (rand() % 100 == 1)
			refs.push_back(ComponentRef<IntComponent>(i));
	}


	std::cout << "insertions: " << count << std::endl;
	std::cout << "deletions: " << refs.size() << std::endl;

	for (int i = 0; i < count; i++)
	{
		store.CreateInstance();
	}

	for (int i = 0; i < refs.size(); i++)
	{
		store.DeleteInstance(refs[i]);
		if (i%100 == 0)
			std::cout << i << " of " << refs.size() << std::endl;
	}


	return 0;
}