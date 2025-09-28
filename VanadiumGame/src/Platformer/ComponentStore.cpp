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


// TODO: fix binary search
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
	{
		return (left + right) / 2;

		for (int i = 0; i < Lookups.size(); i++)
		{
			if (Lookups[i].Id == id)
				return i;
		}

		return -1;
	}

	return (left + right) / 2;
}

unsigned int ComponentTracker::GetComponentIndex(unsigned int id)
{
	unsigned int index = FindLookupIndex(id);
	if (index == -1)
		throw "a";
	return Lookups[index].ComponentIndex;
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


	std::vector<ComponentLookup> buffer(Lookups.size());

	std::vector<ComponentLookup>* writeTo = &buffer;
	std::vector<ComponentLookup>* readFrom = &Lookups;

	int layerSize = 1;

	int totalValues = Lookups.size();

	while (layerSize < totalValues)
	{
		int pointer = 0;
		while (pointer + layerSize <= totalValues)
		{
			int leftPointerOffset = 0;
			int rightPointerOffset = 0;

			int rightLayerSize = std::min(layerSize, totalValues - pointer - layerSize);

			for (int i = 0; i < layerSize + rightLayerSize; i++)
				if (leftPointerOffset >= layerSize)
					(*writeTo)[pointer + i] = (*readFrom)[pointer + layerSize + rightPointerOffset++];
				else if (rightPointerOffset >= rightLayerSize)
					(*writeTo)[pointer + i] = (*readFrom)[pointer + leftPointerOffset++];
				else
					if ((*readFrom)[pointer + leftPointerOffset].Id > (*readFrom)[pointer + layerSize + rightPointerOffset].Id)
						(*writeTo)[pointer + i] = (*readFrom)[pointer + layerSize + rightPointerOffset++];
					else
						(*writeTo)[pointer + i] = (*readFrom)[pointer + leftPointerOffset++];

			pointer += layerSize * 2;
		}



		for (int i = pointer; i < totalValues; i++)
		{
			(*writeTo)[i] = (*readFrom)[i];
		}

		std::swap(readFrom, writeTo);

		layerSize *= 2;
	}

	Lookups.swap(*readFrom);





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