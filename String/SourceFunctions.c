#include "StringDeclare.h"

inline Void StringInit_s(DevString self, const CString data, Size dataLength)
{
	self->length = self->capacity = dataLength;
	allocate(to_link(Data, self->data), sizeof(Char) * dataLength);
	copyData(self->data, 0, data, 0, dataLength);
}

inline Void StringClearData_s(DevString self)
{
	destroy(to_link(Data, self->data));
	self->data = NULL;
}

inline Void StringAssign_s(DevString self, const CString data, Size dataLength)
{
	if (self->data == NULL)
	{
		StringInit_s(self, data, dataLength);
	}
	else if (self->capacity >= dataLength)
	{
		copyData(self->data, 0, data, 0, dataLength);
		self->length = dataLength;
	}
	else
	{
		StringClearData_s(self);
		StringInit_s(self, data, dataLength);
	}
}

inline Void StringIncreaseCapacity_s(DevString self, Size elementsCount)
{
	self->capacity += self->capacity / 2 + elementsCount;
}

inline Void StringReallocate_s(DevString self, Size newLength, Size copy)
{
	Char* temp = self->data;
	self->data = NULL;
	allocate(to_link(Data, self->data), sizeof(Char) * newLength);
	copyData(self->data, 0, temp, 0, self->length);
	destroy(to_link(Data, temp));
}

inline Void StringAdd_s(DevString self, const CString data, Size dataLength)
{
	if (self->data == NULL)
	{
		StringInit_s(self, data, dataLength);
	}
	else if (self->capacity - self->length < dataLength)
	{
		StringIncreaseCapacity_s(self, dataLength);
		StringReallocate_s(self, self->capacity, self->length);
		copyData(self->data, self->length, data, 0, dataLength);
		self->length += dataLength;
	}
}

inline Bool StringInsert_s(DevString self, Index place, const CString data, Size dataLength)
{
	if (self->data == NULL || place > self->length)
	{
		return False;
	}

	if (self->capacity - self->length < dataLength)
	{
		StringIncreaseCapacity_s(self, dataLength);

		Char* temp = self->data;

		self->data = NULL;

		allocate(to_link(Data, self->data), sizeof(Char) * self->capacity);

		copyData(self->data, 0, temp, 0, place);
		copyData(self->data, place + dataLength, temp, place, self->length - place);

	}
	else
	{
		shiftDataRight(self->data, self->length, place, dataLength);
	}

	copyData(self->data, place, data, 0, dataLength);

	self->length += dataLength;

	return True;
}

inline CString StringFindFirst_s(String object, CString found, Size foundSize, Link(Size) indexBuffer)
{
	unpackSelf

	CString coincidence = findÑoincidence(self->data, self->length, found, foundSize);

	if (coincidence != NULL && indexBuffer.object != NULL)
	{
		to_obj(indexBuffer) = coincidence - self->data;
	}

	return coincidence;
}

inline Size StringReplace_s(String object, CString replaceable, Size replaceableSize, CString replacement, Size replacementSize)
{
	unpackSelf

	Size replaceCount = 0;

	CString found = self->data;
	CString end = self->data + self->length;

	if (replaceableSize == replacementSize)
	{
		while (found != NULL && found < end)
		{
			found = findÑoincidence(found, end - found, replaceable, replaceableSize);

			copyData(found, 0, replacement, 0, replaceableSize);

			found += replaceableSize;

			++replaceCount;
		}

	}
	else
	{
		while (found != NULL && found < end)
		{
			found = findÑoincidence(found, end - found, replaceable, replaceableSize);

			StringCut(object, found - self->data, replaceableSize);

			StringInsert_s(object.self, found - self->data, replacement, replacementSize);

			found += replaceableSize;

			++replaceCount;
		}
	}

	return replaceCount;
}

inline Size StringCutAll_s(String object, CString cut, Size cutSize)
{
	unpackSelf
	
	Size count = 0;
	CString end = self->data + self->length, found = findÑoincidence(self->data, end - self->data, cut, cutSize);

	while (found != NULL && found < end)
	{
		StringCut(object, found - self->data, cutSize);
		found = findÑoincidence(found, end - found, cut, cutSize);
		++count;
	}

	return count;
}

inline Size StringCount_s(String object, CString find, Size findSize)
{
	unpackSelf

	Size count = 0;
	CString found = findÑoincidence(self->data, self->length, find, findSize), end = self->data + self->length;

	while (found < end && found != NULL)
	{
		++count;
		found = findÑoincidence(self->data, self->length, find, findSize);
	}

	return count;
}

inline Bool StringEqual_s(String object, CString compared, Size comparedSize)
{
	unpackSelf
	
	if(self->length != comparedSize)
	{
		return False;
	}

	return equalData(self->data, 0, compared, 0, comparedSize);
}
