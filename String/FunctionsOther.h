#ifndef _FUNCTIONSOTHER_H_
#define _FUNCTIONSOTHER_H_

#include "StringDeclare.h"

extern inline Void StringInitOther(String object, String other);

extern inline Void StringAssignOther(String object, String other);

extern inline Bool StringInsertOther(String object, Index place, String other);

extern inline CString StringFindFirstOther(String object, String other, Link(Size) indexBuffer);

extern inline Size StringReplaceOther(String object, String replaceable, String replacement);

extern inline Size StringCutAllOther(String object, String cut);

extern inline Size StringCountOther(String object, String other);

extern inline Void StringAddOther(String object, String other);

inline Bool StringEqualOther(String object, String other);

#endif // !
