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

	const int count = 100000;
	std::vector<ComponentRef<IntComponent>> refsToDelete;
	std::vector<ComponentRef<IntComponent>> refsToRead;

	for (int i = 0; i < count; i++)
	{
		if (rand() % 100 == 1)
			refsToDelete.push_back(ComponentRef<IntComponent>(i));
		else
			refsToRead.push_back(ComponentRef<IntComponent>(i));
	}


	std::cout << "insertions: " << count << std::endl;
	std::cout << "deletions: " << refsToDelete.size() << std::endl;

	for (int i = 0; i < count; i++)
	{
		store.CreateInstance();
	}

	for (int i = 0; i < refsToDelete.size(); i++)
	{
		store.GetComponent(ComponentRef<IntComponent>(refsToDelete[i]));
	}

	for (int i = 0; i < refsToDelete.size(); i++)
	{
		store.DeleteInstance(refsToDelete[i]);
		if (i % 100 == 0)
			std::cout << i << " of " << refsToDelete.size() << std::endl;
	}

	for (int i = 0; i < refsToRead.size(); i++)
	{
		store.GetComponent(ComponentRef<IntComponent>(refsToRead[i]));
	}

	std::cout << "success" << std::endl;

	return 0;
}