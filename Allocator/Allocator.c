#include "Allocator.h"
#include <malloc.h>

#define HEADER (sizeof(IntMax))

Byte* heap = NULL, *maxFree;
IntMax heapSize = 0, maxFreeSize, freeBlocks = 0;

Data getHeap()
{
	return heap;
}

Size getHeapSize()
{
	return heapSize;
}

Bool createHeap(IntMax bytesCount)
{
	if(bytesCount < 0 || heap != NULL)
	{
		return False;
	}

	heap = malloc(bytesCount + sizeof(Size));
	
	if(heap == NULL)
	{
		return False;
	}

	heapSize = bytesCount;
	
	*(Size*)heap = bytesCount;

	maxFree = heap;
	maxFreeSize = heapSize;

	freeBlocks = 1;

	return True;
}

inline Void findMaxFree()
{
	Size counter = freeBlocks;
		
	IntMax maxSize = 0;

	Byte* i = heap, *max = NULL;

	while(counter > 0)
	{
		if(*(IntMax*)i > maxSize)
		{
			max = i;
			maxSize = *(IntMax*)i;
			--counter;
		}

		i += abs(*(IntMax*)i) + HEADER;
	}

	maxFree = max;

	maxFreeSize = maxSize;
}

inline Byte* findFree(IntMax bytes)
{
	if(freeBlocks == 1)
	{
		return maxFree;
	}

	Size temp = freeBlocks;
	IntMax maxSize = 0;
	Byte* i = heap;
	Byte* max = NULL;

	while (temp > 0)
	{
		if(*(IntMax*)i == bytes)
		{
			return i;
		}
		else if(*(IntMax*)i >= bytes && *(IntMax*)i > maxSize)
		{
			max = i;
			maxSize = *(IntMax*)i;
		}
		if (*(IntMax*)i > 0)
		{
			--temp;
		}

		i += abs(*(IntMax*)i) + HEADER;
	}

	return max;
}

inline Void findNeighbours(Byte* object, IntMax objectSize, Link(Data) leftNeighbour, Link(Data) rightNeighbour)
{
	Size counter = freeBlocks;

	Byte* neighbour = object + HEADER + objectSize;

	Data left = NULL, right = NULL;

	if(neighbour < heap + heapSize && *(IntMax*)(neighbour) > 0)
	{
		right = (neighbour);
		--counter;
	}

	Byte* i = heap;

	while (counter > 0 && i < object)
	{
		if(*(IntMax*)i > 0)
		{
			--counter;
			if (i + *(IntMax*)i + HEADER == object)
			{
				left = i;
				break;
			}
		}

		i += abs(*(IntMax*)i) + HEADER;
	}

	to_obj(leftNeighbour) = left;
	to_obj(rightNeighbour) = right;
}

Size allocateMemory(Link(Data) buffer, IntMax bytesCount)
{
	if(freeBlocks == 0 || bytesCount > maxFreeSize || buffer.object == NULL || to_obj(buffer) != NULL)
	{
		return 0;
	}
	
	Byte* temp = findFree(bytesCount);

	IntMax tempSize = *(IntMax*)temp;

	tempSize -= bytesCount;

	if(tempSize < 2 * HEADER)
	{
		bytesCount += tempSize;
		--freeBlocks;
	}
	else
	{
		*(IntMax*)(temp + HEADER + bytesCount) = tempSize - HEADER;
	}

	*(IntMax*)temp = -bytesCount;

	if (temp == maxFree)
	{
		findMaxFree();
	}

	to_obj(buffer) = temp + HEADER;

	return bytesCount;
}

Bool freeMemory(Link(Data) buffer)
{
	if (buffer.object == NULL || to_obj(buffer) < heap || to_obj(buffer) >= heap + heapSize + HEADER)
	{
		return False;
	}

	Byte* temp = (Byte*)to_obj(buffer) - HEADER;

	IntMax tempSize = *(IntMax*)temp;

	if(tempSize > 0)
	{
		return False;
	}

	to_obj(buffer) = NULL;

	tempSize = -tempSize;

	if(freeBlocks == 0)
	{
		maxFree = temp;
		++freeBlocks;
	}
	else
	{
		Byte *left, *right;

		findNeighbours(temp, tempSize, to_link(Data,left), to_link(Data, right));

		if (left != NULL && right != NULL)
		{
			--freeBlocks;
		}
		else if(left == NULL && right == NULL)
		{
			++freeBlocks;
		}
		
		if(right != NULL)
		{
			tempSize += *(IntMax*)right + HEADER;
		}

		if(left != NULL)
		{
			tempSize += *(IntMax*)left + HEADER;
			temp = left;
		}

		if(tempSize > maxFreeSize)
		{
			maxFree = temp;
		}
	}

	if (temp == maxFree)
	{
		maxFreeSize = tempSize;
	}

	*(IntMax*)temp = tempSize;

	return True;
}

Size getFreeBlocksCount()
{
	return freeBlocks;
}

Size getMaxFreeSize()
{
	return maxFreeSize;
}

Bool freeHeap()
{
	if(heap != NULL)
	{
		free(heap);
		freeBlocks = maxFreeSize = heapSize = 0;
		heap = maxFree = NULL;

		return True;
	}

	return False;
}
