#ifndef _STRINGDECLARE_H_
#define _STRINGDECLARE_H_

#include "String.h"

struct _String
{
	Size length, capacity;
	Char* data;
};

typedef struct _String* DevString;

#define unpackSelf DevString self = object.self;

#include "SourceFunctions.h"

#endif
