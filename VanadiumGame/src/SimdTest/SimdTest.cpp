#include "SimdTest.h"
#include <immintrin.h>

int func()
{
	return 1;
}

void Comparison(std::vector<int>& list)
{
	std::vector<int> buffer(list.size());

	std::vector<int>* writeTo = &buffer;
	std::vector<int>* readFrom = &list;

	int layerSize = 1;

	int totalValues = list.size();

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
					if ((*readFrom)[pointer + leftPointerOffset] > (*readFrom)[pointer + layerSize + rightPointerOffset])
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

	list.swap(*readFrom);
}




void SimdTest(std::vector<int>& list)
{
	std::vector<int> buffer(list.size());

	std::vector<int>* writeTo = &buffer;
	std::vector<int>* readFrom = &list;

	int layerSize = 1;

	int totalValues = list.size();

	{
		int pointer = 0;
		while (pointer + layerSize * 7 <= totalValues)
		{
			int leftPointerOffset1 = 0, rightPointerOffset1 = 0;
			int leftPointerOffset2 = 0, rightPointerOffset2 = 0;
			int leftPointerOffset3 = 0, rightPointerOffset3 = 0;
			int leftPointerOffset4 = 0, rightPointerOffset4 = 0;

			// precompute per-run right sizes
			int rightLayerSize1 = std::min(layerSize, totalValues - (pointer + layerSize));
			int rightLayerSize2 = std::min(layerSize, totalValues - (pointer + 2 * layerSize + layerSize));
			int rightLayerSize3 = std::min(layerSize, totalValues - (pointer + 4 * layerSize + layerSize));
			int rightLayerSize4 = std::min(layerSize, totalValues - (pointer + 6 * layerSize + layerSize));

			// pointers for your runs
			int* L[4] = { &(*readFrom)[pointer + 0 * layerSize],
							&(*readFrom)[pointer + 2 * layerSize],
							&(*readFrom)[pointer + 4 * layerSize],
							&(*readFrom)[pointer + 6 * layerSize] };

			int* R[4] = { &(*readFrom)[pointer + layerSize + 0 * layerSize],
							&(*readFrom)[pointer + 3 * layerSize],
							&(*readFrom)[pointer + 5 * layerSize],
							&(*readFrom)[pointer + 7 * layerSize] };

			int leftOffset[4] = { leftPointerOffset1, leftPointerOffset2, leftPointerOffset3, leftPointerOffset4 };
			int rightOffset[4] = { rightPointerOffset1, rightPointerOffset2, rightPointerOffset3, rightPointerOffset4 };
			int rightSize[4] = { rightLayerSize1, rightLayerSize2, rightLayerSize3, rightLayerSize4 };

			for (int i = 0; i < layerSize * 2; i++)
			{
				// load 1 element per run into SIMD lanes
				__m128 leftVals = _mm_set_ps(L[3][leftOffset[3]], L[2][leftOffset[2]], L[1][leftOffset[1]], L[0][leftOffset[0]]);
				__m128 rightVals = _mm_set_ps(R[3][rightOffset[3]], R[2][rightOffset[2]], R[1][rightOffset[1]], R[0][rightOffset[0]]);

				// compare left vs right: returns 0xFFFFFFFF in lane if left > right
				__m128 cmpMask = _mm_cmpgt_ps(leftVals, rightVals);

				// extract mask to 4-bit integer
				int mask = _mm_movemask_ps(cmpMask);

				// write the winner per run
				for (int k = 0; k < 4; k++)
				{
					// check if run k is exhausted
					bool leftDone = leftOffset[k] >= layerSize;
					bool rightDone = rightOffset[k] >= rightSize[k];

					int outIndex = pointer + i + 2 * layerSize * k;

					if (leftDone)
						(*writeTo)[outIndex] = R[k][rightOffset[k]++];
					else if (rightDone)
						(*writeTo)[outIndex] = L[k][leftOffset[k]++];
					else
					{
						// choose based on SIMD comparison
						if (mask & (1 << k))
							(*writeTo)[outIndex] = R[k][rightOffset[k]++];
						else
							(*writeTo)[outIndex] = L[k][leftOffset[k]++];
					}
				}
			}

			pointer += 8 * layerSize; // advance past 4 runs

		}

		for (int i = pointer; i < totalValues; i++)
		{
			(*writeTo)[i] = (*readFrom)[i];
		}

		std::swap(readFrom, writeTo);
	}



	layerSize *= 2;

	while (layerSize < totalValues)
	{
		int pointer = 0;
		while (pointer + layerSize <= totalValues)
		{
			int leftPointerOffset = 0;
			int rightPointerOffset = 0;

			int rightLayerSize = std::min(layerSize, totalValues - pointer - layerSize);

			for (int i = 0; true; i++)
			{
				if (leftPointerOffset >= layerSize)
				{
					for (int j = 0; j < rightLayerSize - rightPointerOffset; j++)
					{
						(*writeTo)[pointer + i + j] = (*readFrom)[pointer + layerSize + rightPointerOffset + j];
					}
					break;
				}
				else if (rightPointerOffset >= rightLayerSize)
				{
					for (int j = 0; j < layerSize - leftPointerOffset; j++)
					{
						(*writeTo)[pointer + i + j] = (*readFrom)[pointer + leftPointerOffset + j];
					}
					break;
				}

				if ((*readFrom)[pointer + leftPointerOffset] > (*readFrom)[pointer + layerSize + rightPointerOffset])
				{
					(*writeTo)[pointer + i] = (*readFrom)[pointer + layerSize + rightPointerOffset];
					rightPointerOffset++;
				}
				else
				{
					(*writeTo)[pointer + i] = (*readFrom)[pointer + leftPointerOffset];
					leftPointerOffset++;
				}
			}

			pointer += layerSize * 2;
		}

		for (int i = pointer; i < totalValues; i++)
		{
			(*writeTo)[i] = (*readFrom)[i];
		}

		std::swap(readFrom, writeTo);

		layerSize *= 2;
	}

	list.swap(*readFrom);
}

