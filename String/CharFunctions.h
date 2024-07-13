#ifndef _CHARFUNCTIONS_H_
#define _CHARFUNCTIONS_H_

#include "StringDeclare.h"

extern inline Void StringAddChar(String object, Char C);

extern inline Bool StringInsertChar(String object, Index place, Char C);

extern inline Char StringPopEndChar(String object);

extern inline Char StringCutChar(String object, Index place);

extern inline CString StringFindFirstChar(String object, Char found, Link(Size) indexBuffer);

extern inline Size StringCutAllChar(String object, Char cut);

extern inline Size StringReplaceChar(String object, Char replaceable, Char replacement);

extern inline Size StringCountChar(String object, Char find);

#endif
