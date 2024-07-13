#include "StringDeclare.h"

inline Void StringInitOther(String object, String other)
{
	if (other.self->data != NULL)
	{
		StringInit_s(object.self, other.self->data, other.self->length);
	}
	else
	{
		StringDefault(object);
	}
}

inline Void StringAssignOther(String object, String other)
{
	if (other.self->data == NULL)
	{
		StringClear(object);
	}
	else
	{
		StringAssign_s(object.self, other.self->data, other.self->length);
	}
}

inline Bool StringInsertOther(String object, Index place, String other)
{
	return StringInsert_s(object.self, place, other.self->data, other.self->length);
}

inline CString StringFindFirstOther(String object, String other, Link(Size) indexBuffer)
{
	return StringFindFirst_s(object, other.self->data, other.self->length, indexBuffer);
}

inline Size StringReplaceOther(String object, String replaceable, String replacement)
{
	return StringReplace_s(object, replaceable.self->data, replaceable.self->length, replacement.self->data, replacement.self->length);
}

inline Size StringCutAllOther(String object, String cut)
{
	return StringCutAll_s(object, cut.self->data, cut.self->length);
}

inline Size StringCountOther(String object, String other)
{
	return StringCount_s(object, other.self->data, other.self->length);
}

inline Void StringAddOther(String object, String other)
{
	if (other.self->data != NULL)
	{
		StringAdd_s(object.self, other.self->data, other.self->length);
	}
}

inline Bool StringEqualOther(String object, String other)
{
	return StringEqual_s(object, other.self->data, other.self->length);
}
