#ifndef _SOURCEFUNCTIONS_H_
#define _SOURCEFUNCTIONS_H_

#include "StringDeclare.h"

extern inline Void StringInit_s(DevString self, const CString data, Size dataLength);

extern inline Void StringClearData_s(DevString self);

extern inline Void StringAssign_s(DevString self, const CString data, Size dataLength);

extern inline Void StringIncreaseCapacity_s(DevString self, Size elementsCount);

extern inline Void StringReallocate_s(DevString self, Size newLength, Size copy);

extern inline Void StringAdd_s(DevString self, const CString data, Size dataLength);

extern inline Bool StringInsert_s(DevString self, Index place, const CString data, Size dataLength);

extern inline CString StringFindFirst_s(String object, CString found, Size foundSize, Link(Size) indexBuffer);

extern inline Size StringReplace_s(String object, CString replaceable, Size replaceableSize, CString replacement, Size replacementSize);

extern inline Size StringCutAll_s(String object, CString cut, Size cutSize);

extern inline Size StringCount_s(String object, CString find, Size findSize);

extern inline Bool StringEqual_s(String object, CString compared, Size comparedSize);

#endif