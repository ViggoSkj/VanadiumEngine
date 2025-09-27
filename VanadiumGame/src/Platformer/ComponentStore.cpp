#include "ComponentStore.h"

void ComponentTracker::InsertLookup(unsigned int id, unsigned int componentIndex)
{
	if (EmptySlots.size() == 0)
	{
		Lookups.emplace_back(id, componentIndex);
		return;
	}

	Lookups[EmptySlots.back()] = ComponentLookup(id, componentIndex);
	EmptySlots.pop_back();

}

unsigned int ComponentTracker::FindLookupIndex(unsigned int id)
{

	int left = 0;
	int right = Lookups.size() - 1;
	int foundId;
	int maxIterations = log2(Lookups.size()) + 2;

	int i = 0;
	while ((foundId = Lookups[(left + right)/2].Id) != id && i < maxIterations)
	{
		if (foundId <= id)
			left = ceil((left + right) / 2.0f);
		else
			right = floor((left + right) / 2.0f);

		i++;
	}

	if (i == maxIterations)
		return -1;

	return (left + right) / 2;
}

unsigned int ComponentTracker::MarkRemoved(unsigned int id)
{
	unsigned int lookupIndex = FindLookupIndex(id);

	if (lookupIndex == -1)
		throw "dasdas";

	EmptySlots.push_back(lookupIndex);
	return Lookups[lookupIndex].ComponentIndex;
}

void ComponentTracker::Sort()
{
	int layerSize = 1;

	int totalValues = Lookups.size();

	while (layerSize < totalValues)
	{
		int pointer = 0;
		while (pointer + layerSize < totalValues)
		{
			int leftPointer = pointer;
			int rightPointer = pointer + layerSize;

			int valuesLeft = std::min(layerSize * 2, totalValues - pointer);
			int lastIndex = pointer + valuesLeft - 1;

			while (rightPointer <= lastIndex && leftPointer <= lastIndex)
			{
				if (Lookups[leftPointer].Id >= Lookups[rightPointer].Id)
				{
					std::swap(Lookups[leftPointer], Lookups[rightPointer]);
					rightPointer++;
				}

				leftPointer++;
			}
			pointer += layerSize * 2;
		}
		layerSize *= 2;
	}
}

void ComponentTracker::Flush()
{
	for (int i = 0; i < EmptySlots.size(); i++)
	{
		std::swap(Lookups[EmptySlots[i]], Lookups[Lookups.size() - 1 - i]);
	}
	Lookups.resize(Lookups.size() - EmptySlots.size());
	EmptySlots.clear();

	Sort();
}

void ComponentTracker::UpdateComponentIndex(unsigned int id, unsigned int newComponentIndex)
{
	unsigned int lookupIndex = FindLookupIndex(id);

	if (lookupIndex == -1)
		throw "dasdas";

	Lookups[lookupIndex].ComponentIndex = newComponentIndex;
}