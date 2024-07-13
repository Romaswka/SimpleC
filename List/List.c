#include "ListDeclare.h"

Bool NodeInit(Node **node, Element element)
{
	*node = NULL;

	if (allocate(to_link(Data, *node), sizeof(Node)) == 0)
	{
		return False;
	}

	(*node)->next = NULL;
	(*node)->value.byteSize = 0;
	(*node)->value.data = NULL;
	
	if (element.byteSize <= sizeof(Data))
	{
		(*node)->value.data = element.data;
	}
	else if (allocate(to_link(Data, (*node)->value.data), element.byteSize) == 0)
	{
		return False;
	}
	else
	{
		copyData((*node)->value.data, 0, element.data, 0, element.byteSize);
	}

	(*node)->value.byteSize = element.byteSize;

	return True;
}

Bool NodeDelete(Node* node)
{
	if (node->value.byteSize > sizeof(Data))
	{
		if (destroy(to_link(Data, node->value.data)) == False)
		{
			return False;
		}
	}

	if (destroy(to_link(Data, node)) == False)
	{
		return False;
	}

	return True;
}

inline Void ListSet_s(_List* self, Node* start, Node* end, Size count)
{
	self->start = start;
	self->count = count;
}

Bool ListDefault(List object)
{
	unpackSelf;
	ListSet_s(self, NULL, NULL, 0);
	return True;
}

Bool ListInit_s(_List* self, Element data[], Size elementsCount)
{
	if (NodeInit(&(self->start), data[0]) == False)
	{
		return False;
	}

	Node** temp = &(self->start);

	for (Size i = 1; i < elementsCount; ++i)
	{
		temp = &((*temp)->next);
		if (NodeInit(temp, data[i]) == False)
		{
			return False;
		}
	}

	self->end = *temp;

	self->count = elementsCount;

	return True;
}

Bool ListInit(List object, Element data[], Size elementsCount)
{
	unpackSelf;

	if(self->count != 0 || self->start != NULL || data == NULL || elementsCount == 0)
	{
		return False;
	}

	return ListInit_s(self, data, elementsCount);
}

Bool ListInitByteArray(List object, Byte data[], Size elementSize, Size elementsCount)
{
	unpackSelf;

	if(self->start != NULL || self->count != 0 || data == NULL || elementSize == 0 || elementsCount == 0)
	{
		return False;
	}

	Node** temp = &(self->start);

	Element tempElement;

	tempElement.byteSize = elementSize;

	Bool isStruct = elementsCount > sizeof(Data);

	for(Index i = 0; i < elementsCount; ++i)
	{
		tempElement.data = data + i * elementSize;

		if(isStruct == False)
		{
			moveAccordSize(to_link(Void, tempElement.data), (Link(Void)) { tempElement.data }, elementSize));
		}

		if(NodeInit(temp, tempElement) == False)
		{
			return False;
		}

		temp = &(temp->next);
	}

	self->end = *temp;

	return True;
}

Bool ListPush(List object, Element add)
{
	if(add.byteSize == 0)
	{
		return False;
	}

	unpackSelf;

	Node** temp;

	if(self->start == NULL)
	{
		temp = &(self->start);
	}
	else
	{
		temp = &(self->end->next);
	}

	if(NodeInit(temp, add) == False)
	{
		return False;
	}

	self->end = *temp;

	self->count += 1;

	return True;
}

Bool ListStart(List object, ListIterator buffer)
{
	unpackSelf;

	if(buffer.self == NULL)
	{
		return False;
	}

	buffer.self->object = self->start;

	return True;
}

Bool ListEnd(List object, ListIterator buffer)
{
	unpackSelf;

	if (buffer.self == NULL)
	{
		return False;
	}

	buffer.self->object = self->end;

	return True;
}

Bool LINext(ListIterator iterator)
{
	if(iterator.self == NULL)
	{
		return False;
	}

	Node* temp = iterator.self->object;

	if(temp == NULL)
	{
		return False;
	}
	
	iterator.self->object = temp->next;

	return True;
}

Bool LIGet(ListIterator iterator, Link(Element) buffer)
{
	if(iterator.self == NULL)
	{
		return False;
	}

	Node* temp = iterator.self->object;

	if (temp == NULL)
	{
		return False;
	}

	to_obj(buffer) = temp->value;

	return True;
}

Bool LIChange(ListIterator iterator, Element element)
{
	if(iterator.self == NULL || element.byteSize == 0)
	{
		return False;
	}

	Node* temp = iterator.self->object;

	if(temp == NULL || temp->value.byteSize != element.byteSize)
	{
		return False;
	}

	if(element.byteSize > sizeof(Data))
	{
		if(element.data == NULL)
		{
			return False;
		}

		copyData(temp->value.data, 0, element.data, 0, element.byteSize);
	}
	else
	{
		temp->value.data = element.data;
	}

	return True;
}

Bool LISet(ListIterator iterator, Element element)
{
	if(iterator.self == NULL)
	{
		return False;
	}

	Node* temp = iterator.self->object;

	if(temp == NULL)
	{
		return False;
	}

	if(temp->value.byteSize > sizeof(Data))
	{
		if (temp->value.byteSize != element.byteSize)
		{
			if (destroy(to_link(Data, temp->value.data)) == False || allocate(to_link(Data, temp->value.data), element.byteSize) == 0)
			{
				return False;
			}
		}

		copyData(temp->value.data, 0, element.data, 0, element.byteSize);
	}
	else
	{
		temp->value.data = element.data;
	}

	if (temp->value.byteSize != element.byteSize)
	{
		temp->value.byteSize = element.byteSize;
	}

	return True;
}

Bool ListClear(List object)
{
	unpackSelf;
	
	if(self->start == NULL || self->count == 0)
	{
		return False;
	}

	Node* temp;

	for(; self->start != NULL; self->start = temp)
	{
		temp = self->start->next;
		
		if(NodeDelete(temp) == False)
		{
			return False;
		}
	}

	self->end = NULL;

	self->count = 0;

	return True;
}

Bool LI_IsNull(ListIterator iterator)
{
	if(iterator.self == NULL)
	{
		return True;
	}

	Node* temp = iterator.self->object;

	return temp == NULL;
}

Bool ListAdd(List object, List other)
{
	unpackSelf;
	
	_List otherSelf = other.self;

	if(otherSelf == NULL || otherSelf.start == NULL || otherSelf.count == 0)
	{
		return False;
	}

	if(self->start == NULL)
	{
		
	}
}
