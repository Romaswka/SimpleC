#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <Preparings.h>
#include <Allocator.h>
#include <List.h>
#include <assert.h>

setAllocate(allocateMemory);
setDestroy(freeMemory);

#define SIZE 0xffff

int main()
{
	createHeap(SIZE);

	List dL(a);

	ListDefault(a);

	size_t index = 0;

	Element buffer;

	ListIterator dLI(i);

	for (ListStart(a, i); LI_IsNull(i) == False; LINext(i))
	{
		LIGet(i, to_link(Element, buffer));
		printf("index: %llu, size: %llu, value: %llu\n", index, buffer.byteSize, (Size)buffer.data);
		++index;
	}

	freeHeap();

	system("pause");

	return 0;
}