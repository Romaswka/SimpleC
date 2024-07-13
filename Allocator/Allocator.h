#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <DataTypes.h>

Bool createHeap(IntMax bytesCount);

Data getHeap();

Size getHeapSize();

Size allocateMemory(Link(Data) buffer, IntMax bytesCount);

Bool freeMemory(Link(Data) buffer);

Size getFreeBlocksCount();

Size getMaxFreeSize();

Bool freeHeap();

#endif