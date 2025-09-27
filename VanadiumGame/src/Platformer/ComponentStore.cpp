#include "ComponentStore.h"

void ComponentTracker::Flush()
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
