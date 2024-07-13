#include "StringDeclare.h"

inline Void StringAddChar(String object, Char C)
{
	unpackSelf
	
	if (self->data == NULL)
	{
		self->capacity = 1;
		allocate(to_link(Data, self->data), 1 * sizeof(Char));
	}
	else if (self->capacity == self->length)
	{
		StringIncreaseCapacity_s(self, 1);
		StringReallocate_s(self, self->capacity, self->length);
	}

	self->data[self->length] = C;
	++(self->length);
}

inline Bool StringInsertChar(String object, Index place, Char C)
{
	unpackSelf
		if (self->data == NULL || place >= self->length)
		{
			return False;
		}

	if (self->capacity == self->length)
	{
		StringIncreaseCapacity_s(self, 1);

		Char* temp = self->data;

		allocate(to_link(Data, self->data), sizeof(Char) * self->capacity);

		copyData(self->data, 0, temp, 0, place);

		copyData(self->data, place + 1, temp, place, self->length - place);
	}
	else
	{
		shiftDataRight(self->data, self->length, place, sizeof(Char));
	}

	self->data[place] = C;
	++(self->length);

	return True;
}

inline Char StringPopEndChar(String object)
{
	unpackSelf
	if (self->length == 0)
	{
		return '\0';
	}

	Char temp = self->data[self->length];

	--(self->length);

	return temp;
}

inline Char StringCutChar(String object, Index place)
{
	unpackSelf

	if(self->length <= place)
	{
		return '\0';
	}

	Char temp = self->data[place];

	copyData(self->data, place, self->data, place + 1, self->length - place - 1);

	--(self->length);

	return temp;
}

inline CString StringFindFirstChar(String object, Char found, Link(Size) indexBuffer)
{
	unpackSelf
	for(Size i = 0; i < self->length; ++i)
	{
		if(self->data[i] == found)
		{
			if(indexBuffer.object != NULL)
			{
				to_obj(indexBuffer) = i;
			}
			return self->data + i;
		}
	}

	return NULL;
}

inline Size StringCutAllChar(String object, Char cut)
{
	unpackSelf
		Size count = 0;
	CString end = self->data + self->length, found = findFirst(self->data, self->length, cut);

	while (found != NULL && found < end)
	{
		StringCutChar(object, found - self->data);
		found = findFirst(self->data, self->length, cut);
		++count;
	}

	return count;
}

inline Size StringReplaceChar(String object, Char replaceable, Char replacement)
{
	unpackSelf

	Size count = 0;

	for (Size i = 0; i < self->length; ++i)
	{
		if (self->data[i] == replaceable)
		{
			self->data[i] = replacement;
			++count;
		}
	}

	return count;
}

inline Size StringCountChar(String object, Char find)
{
	unpackSelf
	
	Size count = 0;

	for(Size i = 0; i < self->length; ++i)
	{
		if(self->data[i] == find)
		{
			++count;
		}
	}

	return count;
}