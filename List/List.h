#ifndef _LIST_H_
#define _LIST_H_

#include <Preparings.h>

struct _List;

typedef struct _List _List;

struct _ListIterator;

typedef struct _ListIterator _ListIterator;

typedef union
{
	const _List* const self;

} List;

typedef union
{
	_ListIterator* self;
} ListIterator;

typedef struct
{
	Size byteSize;
	Data data;

} Element;

defineLinkType(Element);

#define dL(name) name = (List) { (Data[3]) {} }
#define dLI(name) name = (ListIterator) { (Data[1]) {} } 

Bool ListDefault(List object);

Bool ListInit(List object, Element data[], Size elementsCount);

Bool ListInitByteArray(List object, Byte data[], Size elementSize, Size elementsCount);

Bool ListClear(List object);

Bool ListPush(List object, Element add);

Bool ListStart(List object, ListIterator buffer);

Bool ListEnd(List object, ListIterator buffer);

Bool LINext(ListIterator iterator);

Bool LIGet(ListIterator iterator, Link(Element) buffer);

Bool LIChange(ListIterator iterator, Element element);

Bool LISet(ListIterator iterator, Element element);

Bool LI_IsNull(ListIterator iterator);

Bool ListAdd(List object, List other);
#endif
