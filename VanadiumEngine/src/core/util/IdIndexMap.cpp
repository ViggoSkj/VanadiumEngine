#include "IdIndexMap.h"

void IdIndexMap::InsertLookup(unsigned int id, unsigned int componentIndex)
{
	if (EmptySlots.size() == 0)
	{
		Lookups.emplace_back(id, componentIndex);
		return;
	}

	Lookups[EmptySlots.back()] = IdIndexLookup(id, componentIndex);
	EmptySlots.pop_back();

}


// TODO: fix binary search
unsigned int IdIndexMap::FindLookupIndex(unsigned int id)
{
	if (Lookups.size() < 1)
		return -1;

	int left = 0;
	int right = Lookups.size() - 1;
	int foundId;
	int maxIterations = log2(Lookups.size()) + 2;

	int i = 0;
	while ((foundId = Lookups[(left + right) / 2].Id) != id && i < maxIterations)
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

unsigned int IdIndexMap::GetIndex(unsigned int id)
{
	unsigned int index = FindLookupIndex(id);
	if (index == -1)
		throw "a";
	return Lookups[index].Index;
}

unsigned int IdIndexMap::MarkRemoved(unsigned int id)
{
	unsigned int lookupIndex = FindLookupIndex(id);

	if (lookupIndex == -1)
		throw "dasdas";

	EmptySlots.push_back(lookupIndex);
	return Lookups[lookupIndex].Index;
}

void IdIndexMap::Sort()
{


	std::vector<IdIndexLookup> buffer(Lookups.size());

	std::vector<IdIndexLookup>* writeTo = &buffer;
	std::vector<IdIndexLookup>* readFrom = &Lookups;

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

void IdIndexMap::Flush()
{
	for (int i = 0; i < EmptySlots.size(); i++)
	{
		std::swap(Lookups[EmptySlots[i]], Lookups[Lookups.size() - 1 - i]);
	}
	Lookups.resize(Lookups.size() - EmptySlots.size());
	EmptySlots.clear();

	Sort();
}

void IdIndexMap::UpdateIndex(unsigned int id, unsigned int newIndex)
{
	unsigned int lookupIndex = FindLookupIndex(id);

	if (lookupIndex == -1)
		throw "dasdas";

	Lookups[lookupIndex].Index = newIndex;
}