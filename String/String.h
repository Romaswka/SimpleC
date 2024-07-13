#ifndef _STRING_H_
#define _STRING_H_

#include <STD_CFunctions.h>
#include <Preparings.h>

typedef struct _String* DevString;

typedef union String
{
	DevString self;
} String;

const Size StringTypeSize;

#define dS(name) name = (String){(Data[3]){0}}

#define STI(name) (StringData(name))

#include "FunctionsOther.h"
#include "CharFunctions.h"

extern inline Void StringDefault(String object);

extern inline Void StringInit(String object, const CString data);

extern inline Void StringClear(String object);

extern inline Void StringAssign(String object, const CString data);

extern inline Void StringAdd(String object, const CString data);

extern inline Bool StringInsert(String object, Index place, const CString data);

extern inline CString StringData(String object);

extern inline Size StringLength(String object);

extern inline Size StringCapacity(String object);

extern inline Void StringCopy(String object, CString buffer);

extern inline Bool StringAt(String object, Index place, Link(Char) buffer);

extern inline Bool StrinSet(String object, Index place, Char C);

extern inline Void StringEqualizeCapacity(String object);

extern inline CString StringPopEnd(String object, Size count);

extern inline Void StringChangeCapacity (String object, IntMax change);

extern inline Void StringAddSize(String object, Size value);

extern inline Void StringAddInt(String object, IntMax value);

extern inline Void StringAddFloat(String object, Float64 value, UInt8 accuracy);

extern inline Size StringCut(String object, Index cutStart, Size cutSize);

extern inline Size StringCutSlice(String object, Index cutStart, Index cutEnd);

extern inline Size StringCopySlice(String object, Index start, Index end, CString buffer);

extern inline CString StringFindFirst(String object, CString found, Link(Size) indexBuffer);

extern inline Size StringReplace(String object, CString replaceable, CString replacement);

extern inline Size StringReplace_S_CS(String object, String replaceable, CString replacement);

extern inline Size StringReplace_CS_S(String object, CString replaceable, String replacement);

extern inline Size StringCutAll(String object, CString cut);

extern inline Size StringCount(String object, CString find);

extern inline Bool StringEqual(String object, CString compared);

#endif // !_STRING_H_
