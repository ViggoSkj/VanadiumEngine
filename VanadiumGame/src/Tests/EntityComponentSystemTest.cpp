#include "Platformer/ComponentStore.h"
#include <iostream>

class TestIntComponent : public Component
{
public:
	int Value;
};


int Test()
{
	ComponentStore<TestIntComponent> store;

	const int count = 100000;
	std::vector<ComponentRef> refsToDelete;
	std::vector<ComponentRef> refsToRead;

	for (int i = 0; i < count; i++)
	{
		if (rand() % 100 == 1)
			refsToDelete.push_back(ComponentRef(i));
		else
			refsToRead.push_back(ComponentRef(i));
	}


	std::cout << "insertions: " << count << std::endl;
	std::cout << "deletions: " << refsToDelete.size() << std::endl;

	for (int i = 0; i < count; i++)
	{
		store.CreateInstance();
	}

	for (int i = 0; i < refsToDelete.size(); i++)
	{
		store.GetComponent(ComponentRef(refsToDelete[i]));
	}

	for (int i = 0; i < refsToDelete.size(); i++)
	{
		store.DeleteInstance(refsToDelete[i]);
		if (i % 100 == 0)
			std::cout << i << " of " << refsToDelete.size() << std::endl;
	}

	for (int i = 0; i < refsToRead.size(); i++)
	{
		store.GetComponent(ComponentRef(refsToRead[i]));
	}

	std::cout << "success" << std::endl;

	return 0;
}