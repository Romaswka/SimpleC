#include "StringDeclare.h"

const Size StringTypeSize = sizeof(struct _String);

inline Void StringDefault(String object)
{
	unpackSelf
	self->data = NULL;
	self->length = self->capacity = 0;
}

inline Void StringInit(String object, const CString data)
{
	StringInit_s(object.self, data, cstringLength(data));
}

inline Void StringClear(String object)
{
	unpackSelf
	if(self->data != NULL)
	{
		StringClearData_s(self);
		self->capacity = self->length = 0;
	}
}

inline Void StringAssign(String object, const CString data)
{
	StringAssign_s(object.self, data, cstringLength(data));
}

inline Void StringAdd(String object, const CString data)
{
	StringAdd_s(object.self, data, cstringLength(data));
}

inline Bool StringInsert(String object, Index place, const CString data)
{
	return StringInsert_s(object.self, place, data, cstringLength(data));
}

inline CString StringData(String object)
{
	return object.self->data;
}

inline Size StringLength(String object)
{
	return object.self->length;
}

inline Size StringCapacity(String object)
{
	return object.self->capacity;
}

inline Void StringCopy(String object, CString buffer)
{
	copyData(buffer, 0, object.self->data, 0, object.self->length);
}

inline Bool StringAt(String object, Index place, Link(Char) buffer)
{
	unpackSelf
	if(self->data == NULL || self->length < place)
	{
		return False;
	}

	to_obj(buffer) = self->data[place];

	return True;
}

inline Bool StrinSet(String object, Index place, Char C)
{
	unpackSelf
	if(self->data == NULL || self->length < place)
	{
		return False;
	}

	self->data[place] = C;

	return True;
}

inline Void StringEqualizeCapacity(String object)
{
	unpackSelf
	if (self->length == self->capacity)
	{
		return;
	}

	StringReallocate_s(self, self->length, self->length);

	self->capacity = self->length;
}

inline CString StringPopEnd(String object, Size count)
{
	unpackSelf
	if(self->length == 0)
	{
		return NULL;
	}

	if(self->length <= count)
	{
		self->length = 0;
		return self->data;
	}

	self->length -= count;

	return self->data + self->length;
}

inline Void StringChangeCapacity(String object, IntMax change)
{
	unpackSelf
	if(change == 0)
	{
		return;
	}
	
	if(change < 0 && (Size)-change >= self->capacity)
	{
		StringClear(object);
		return;
	}
	else
	{
		self->capacity += change;
	}

	if(self->capacity < self->length)
	{
		self->length = self->capacity;
	}

	StringReallocate_s(self, self->capacity, self->length);
}

inline Void StringAddSize(String object, Size value)
{
	static Byte decimalNumber[21];
	StringAdd_s(object.self, decimalNumber, SizeToCString(value, decimalNumber));
}

inline Void StringAddInt(String object, IntMax value)
{
	static Byte decimalNumber[21];
	StringAdd_s(object.self, decimalNumber, IntToCString(value, decimalNumber));
}

inline Void StringAddFloat(String object, Float64 value, UInt8 accuracy)
{
	static Byte floatNumber[261];
	StringAdd_s(object.self, floatNumber, FloatToCString(value, floatNumber, accuracy));
}

inline Size StringCut(String object, Index cutStart, Size cutSize)
{
	unpackSelf

	copyData(self->data, cutStart, self->data, cutStart + cutSize, cutSize);

	(self->length) -= cutSize;

	return cutSize;
}

inline Size StringCutSlice(String object, Index cutStart, Index cutEnd)
{
	unpackSelf

	Size byteSize = cutEnd - cutStart;

	copyData(self->data, cutStart, self->data, cutEnd, byteSize);

	(self->length) -= byteSize;

	return byteSize;
}

inline Size StringCopySlice(String object, Index start, Index end, CString buffer)
{
	unpackSelf

	Size byteSize = end - start;

	copyData(buffer, 0, self->data, start, byteSize);

	return byteSize;
}

inline CString StringFindFirst(String object, CString found, Link(Size) indexBuffer)
{
	return StringFindFirst_s(object, found, cstringLength(found), indexBuffer);
}

inline Size StringReplace(String object, CString replaceable, CString replacement)
{
	return StringReplace_s(object, replaceable, cstringLength(replaceable), replacement, cstringLength(replacement));
}

inline Size StringReplace_S_CS(String object, String replaceable, CString replacement)
{
	return StringReplace_s(object, replaceable.self->data, replaceable.self->length, replacement, cstringLength(replacement));
}

inline Size StringReplace_CS_S(String object, CString replaceable, String replacement)
{
	return StringReplace_s(object, replaceable, cstringLength(replaceable), replacement.self->data, replacement.self->length);
}

inline Size StringCutAll(String object, CString cut)
{
	return StringCutAll_s(object, cut, cstringLength(cut));
}

inline Size StringCount(String object, CString find)
{
	return StringCount_s(object, find, cstringLength(find));
}

inline Bool StringEqual(String object, CString compared)
{
	return StringEqual_s(object, compared, cstringLength(compared));
}
